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
 https://github.com/apache/kudu/blob/master/src/kudu/util/logging-test.cc

 */

#include <glog/logging.h>
#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>
#include "absl/time/clock.h"
#include "absl/synchronization/barrier.h"

#include "src/base/logger_async.h"
#include "src/base/test/test_util.h"

namespace osp {
// Test that VLOG(n) does not evaluate its message if the verbose level is < n,
// ensuring that it is perf-safe to write things like
//
//   VLOG(1) << Substitute("your foo is $0", compute_costly_bar_string());
//
// in hot code paths.
// NOTE: verbose level define in glog. DECLARE_int32(v);  // in vlog_is_on.cc
TEST(LoggingTest, TestVlogDoesNotEvaluateMessage) {
  if (VLOG_IS_ON(1)) {
    LOG(INFO) << "Test skipped: verbose level is at least 1";
    return;
  }

  int numVlogs = 0;
  VLOG(1) << "This shouldn't be logged: " << numVlogs++;
  ASSERT_EQ(0, numVlogs);
}

// Test Logger implementation that just counts the number of messages
// and flushes.
//
// This is purposefully thread-unsafe because we expect that the
// AsyncLogger is only accessing the underlying logger from a single
// thhread.
class CountingLogger : public google::base::Logger {
 public:
  void Write(bool force_flush,
             time_t /*timestamp*/,
             const char* /*message*/,
             int /*message_len*/) override {
    message_count_++;
    if (force_flush) {
      Flush();
    }
  }

  void Flush() override {
    // Simulate a slow disk.
    absl::SleepFor(absl::Milliseconds(5));
    flush_count_++;
  }

  uint32_t LogSize() override {
    return 0;
  }

  std::atomic<int> flush_count_ = {0};
  std::atomic<int> message_count_ = {0};
};

TEST(LoggingTest, TestAsyncLogger) {
  const int kNumThreads = 4;
  const int kNumMessages = 10000;
  const int kBuffer = 10000;
  CountingLogger base;
  AsyncLogger async(&base, kBuffer);
  async.Start();

  std::vector<std::thread> threads;
  absl::Barrier go_barrier(kNumThreads + 1);
  // Start some threads writing log messages.
  for (int i = 0; i < kNumThreads; i++) {
    threads.emplace_back([&]() {
        go_barrier.Block();
        for (int m = 0; m < kNumMessages; m++) {
          async.Write(true, m, "x", 1);
        }
      });
  }

  // And a thread calling Flush().
  threads.emplace_back([&]() {
      go_barrier.Block();
      for (int i = 0; i < 10; i++) {
        async.Flush();
        absl::SleepFor(absl::Milliseconds(3));
      }
    });

  for (auto& t : threads) {
    t.join();
  }
  async.Stop();
  ASSERT_EQ(base.message_count_, kNumMessages * kNumThreads);
  // The async logger should only flush once per "batch" rather than
  // once per message, even though we wrote every message with
  // 'flush' set to true.
  ASSERT_LT(base.flush_count_, kNumMessages * kNumThreads);
  ASSERT_GT(async.app_threads_blocked_count_for_tests(), 0);
}

TEST(LoggingTest, TestAsyncLoggerAutoFlush) {
  const int kBuffer = 10000;
  CountingLogger base;
  AsyncLogger async(&base, kBuffer);

  FLAGS_logbufsecs = 1;
  async.Start();

  // Write some log messages with non-force_flush types.
  async.Write(false, 0, "test-x", 1);
  async.Write(false, 1, "test-y", 1);

  // The flush wait timeout might take a little bit of time to run.
  ASSERT_EVENTUALLY([&]() {
    ASSERT_EQ(base.message_count_, 2);
    // The AsyncLogger should have flushed at least once by the timer automatically
    // so there should be no more messages in the buffer.
    ASSERT_GT(base.flush_count_, 0);
  });
  async.Stop();
}

}  // namespace osp