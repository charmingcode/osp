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
   Reference from https://github.com/apache/kudu/blob/master/src/kudu/util/logging-test.cc

 */

#include <glog/logging.h>
#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>

namespace osp {
// Test that VLOG(n) does not evaluate its message if the verbose level is < n,
// ensuring that it is perf-safe to write things like
//
//   VLOG(1) << Substitute("your foo is $0", compute_costly_bar_string());
//
// in hot code paths.
TEST(LoggingTest, TestVlogDoesNotEvaluateMessage) {
  if (VLOG_IS_ON(1)) {
    LOG(INFO) << "Test skipped: verbose level is at least 1";
    return;
  }

  int numVlogs = 0;
  VLOG(1) << "This shouldn't be logged: " << numVlogs++;
  ASSERT_EQ(0, numVlogs);
}

} // namespace osp