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
   Reference from https://github.com/apache/kudu/blob/master/src/kudu/util/logging.h
 */


#pragma once

#include <iosfwd>
#include <string>

#include "glog/logging.h"

namespace osp {

// The glog doesn't allow multiple invocations of InitGoogleLogging. This method conditionally
// calls InitGoogleLogging only if it hasn't been called before.
//
// It also takes care of installing the google failure signal handler and
// setting the signal handler for SIGPIPE to SIG_IGN.

// NOTE: thread safe
void InitGoogleLoggingSafe(const char* arg);

// Shuts down the google logging library. Call before exit to ensure that log files are
// flushed.
void ShutdownLoggingSafe();

}

