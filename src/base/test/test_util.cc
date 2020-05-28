/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at

   http://www.apache.org/licenses/LICENSE-2.0

 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 *
   Created on: April 4, 2020
   Reference from
   https://github.com/apache/kudu/blob/master/src/kudu/util/test_util.cc
 */

#include <limits.h>
#include <strings.h>
#include <unistd.h>
#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <limits>
#include <map>
#include <memory>
#include <ostream>
#include <string>
#include <utility>
#include <vector>
#include <gflags/gflags.h>
#include <glog/logging.h>
#include <gtest/gtest-spi.h>

#include "src/base/test/test_util.h"
#include "src/base/scoped_cleanup.h"

DEFINE_string(test_leave_files, "on_failure",
              "Whether to leave test files around after the test run. "
              " Valid values are 'always', 'on_failure', or 'never'");

DEFINE_int32(test_random_seed, 0, "Random seed to use for randomized tests");

DECLARE_string(time_source);

namespace osp {

///////////////////////////////////////////////////
// Test utility functions
///////////////////////////////////////////////////

void AssertEventually(const std::function<void(void)>& f,
                      const absl::Duration& timeout,
                      AssertBackoff backoff) {
  const absl::Time deadline = absl::Now() + timeout;
  {
    // Disable gtest's "on failure" behavior, or else the assertion failures
    // inside our attempts will cause the test to end even though we would
    // like to retry.
    bool old_break_on_failure = testing::FLAGS_gtest_break_on_failure;
    bool old_throw_on_failure = testing::FLAGS_gtest_throw_on_failure;
    auto c = MakeScopedCleanup([old_break_on_failure, old_throw_on_failure]() {
      testing::FLAGS_gtest_break_on_failure = old_break_on_failure;
      testing::FLAGS_gtest_throw_on_failure = old_throw_on_failure;
    });
    testing::FLAGS_gtest_break_on_failure = false;
    testing::FLAGS_gtest_throw_on_failure = false;

    for (int attempts = 0; absl::Now() < deadline; attempts++) {
      // Capture any assertion failures within this scope (i.e. from their function)
      // into 'results'
      testing::TestPartResultArray results;
      testing::ScopedFakeTestPartResultReporter reporter(
          testing::ScopedFakeTestPartResultReporter::INTERCEPT_ONLY_CURRENT_THREAD,
          &results);
      f();

      // Determine whether their function produced any new test failure results.
      bool has_failures = false;
      for (int i = 0; i < results.size(); i++) {
        has_failures |= results.GetTestPartResult(i).failed();
      }
      if (!has_failures) {
        return;
      }

      // If they had failures, sleep and try again.
      int sleep_ms;
      switch (backoff) {
        case AssertBackoff::EXPONENTIAL:
          sleep_ms = (attempts < 10) ? (1 << attempts) : 1000;
          break;
        case AssertBackoff::NONE:
          sleep_ms = 1;
          break;
        default:
          LOG(FATAL) << "Unknown backoff type";
      }
      absl::SleepFor(absl::Milliseconds(sleep_ms));
    }
  }

  // If we ran out of time looping, run their function one more time
  // without capturing its assertions. This way the assertions will
  // propagate back out to the normal test reporter. Of course it's
  // possible that it will pass on this last attempt, but that's OK
  // too, since we aren't trying to be that strict about the deadline.
  f();
  if (testing::Test::HasFatalFailure()) {
    ADD_FAILURE() << "Timed out waiting for assertion to pass.";
  }
}

} // namespace osp