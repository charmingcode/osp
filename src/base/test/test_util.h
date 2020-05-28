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
   https://github.com/apache/kudu/blob/master/src/kudu/util/test_util.h
 */

// Base test class, with various utility functions.
#pragma once

#include <sys/types.h>
#include <cstdint>
#include <functional>
#include <memory>
#include <string>
#include <gtest/gtest.h>
#include "absl/time/time.h"
#include "absl/time/clock.h"

// Detect fatals in the surrounding scope. NO_FATALS() only checks for fatals
// in the expression passed to it.
#define NO_PENDING_FATALS() \
  if (testing::Test::HasFatalFailure()) { return; }

#define SKIP_IF_SLOW_NOT_ALLOWED() do { \
  if (!AllowSlowTests()) { \
    LOG(WARNING) << "test is skipped; set KUDU_ALLOW_SLOW_TESTS=1 to run"; \
    return; \
  } \
} while (0)

#define ASSERT_EVENTUALLY(expr) do { \
  AssertEventually(expr); \
  NO_PENDING_FATALS(); \
} while (0)

namespace google {
class FlagSaver;
} // namespace google

namespace osp {

// Wait until 'f()' succeeds without adding any GTest 'fatal failures'.
// For example:
//
//   AssertEventually([]() {
//     ASSERT_GT(ReadValueOfMetric(), 10);
//   });
//
// The function is run in a loop with optional back-off.
//
// To check whether AssertEventually() eventually succeeded, call
// NO_PENDING_FATALS() afterward, or use ASSERT_EVENTUALLY() which performs
// this check automatically.
enum class AssertBackoff {
  // Use exponential back-off while looping, capped at one second.
  EXPONENTIAL,

  // Sleep for a millisecond while looping.
  NONE,
};

void AssertEventually(const std::function<void(void)>& f,
                      const absl::Duration& timeout = absl::Seconds(30),
                      AssertBackoff backoff = AssertBackoff::EXPONENTIAL);

} // namespace osp