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
   https://github.com/apache/kudu/blob/master/src/kudu/util/logging.cc
 */

#include "src/base/logging.h"
#include "src/base/spin_lock.h"
#include "src/base/logger_async.h"

#include <fstream>
#include <mutex>
#include <string>
#include "absl/strings/str_cat.h"
#include "absl/time/clock.h"
#include "absl/time/time.h"
#include "gflags/gflags.h"

const char* PROJ_NAME = "osp";

DEFINE_string(log_filename, "",
              "Prefix of log filename - "
              "full path is <log_dir>/<log_filename>.[INFO|WARN|ERROR|FATAL]");

DEFINE_bool(log_async, true,
            "Enable asynchronous writing to log files. This improves "
            "latency and stability.");

DEFINE_int32(log_async_buffer_bytes_per_level, 2 * 1024 * 1024,
             "The number of bytes of buffer space used by each log "
             "level. Only relevant when --log_async is enabled.");

DEFINE_int32(
    max_log_files, 10,
    "Maximum number of log files to retain per severity level. The most recent "
    "log files are retained. If set to 0, all log files are retained.");

namespace osp {
namespace {

void EnableAsyncLogging() {
  // Enable Async for every level except for FATAL. Fatal should be synchronous
  // to ensure that we get the fatal log message written before exiting.
  for (auto level : { google::INFO, google::WARNING, google::ERROR }) {
    auto* orig = google::base::GetLogger(level);
    auto* async = new AsyncLogger(orig, FLAGS_log_async_buffer_bytes_per_level);
    async->Start();
    google::base::SetLogger(level, async);
  }
}

} // anonymous namespace

SpinLock logging_lock;

void InitGoogleLoggingSafe(const char* arg) {
  std::lock_guard<SpinLock> l(logging_lock);

  static bool logging_initialized = false;

  if (logging_initialized) return;

  google::InstallFailureSignalHandler();

  if (!FLAGS_log_filename.empty()) {
    for (int severity = google::INFO; severity <= google::FATAL; ++severity) {
      google::SetLogSymlink(severity, FLAGS_log_filename.c_str());
    }
  }

  // This forces our logging to default to /tmp rather than looking for a
  // temporary directory if none is specified. This is done so that we
  // can reliably construct the log file name without duplicating the
  // complex logic that glog uses to guess at a temporary dir.
  CHECK_NE("",
           google::SetCommandLineOptionWithMode(
               "log_dir", "/tmp", google::FlagSettingMode::SET_FLAGS_DEFAULT));

  if (!FLAGS_logtostderr) {
    // Verify that a log file can be created in log_dir by creating a tmp file.
    const std::string file_name =
        absl::StrCat(FLAGS_log_dir, "/", PROJ_NAME, "_test_log.",
                     absl::FormatTime(absl::Now()));
    std::ofstream test_file(file_name.c_str());
    if (!test_file.is_open()) {
      std::ostringstream error_msg;
      error_msg << "Could not open file in log_dir " << FLAGS_log_dir;
      perror(error_msg.str().c_str());
      exit(1);
    }
    remove(file_name.c_str());
  }

  google::InitGoogleLogging(arg);

  // Needs to be done after InitGoogleLogging
  if (FLAGS_log_filename.empty()) {
    CHECK_STRNE(google::ProgramInvocationShortName(), "UNKNOWN")
        << ": must initialize gflags before glog";
    FLAGS_log_filename = google::ProgramInvocationShortName();
  }

  // File logging: on.
  // Stderr logging threshold: FLAGS_stderrthreshold.
  // Sink logging: off.
  // initial_stderr_severity = FLAGS_stderrthreshold;

  // Ignore SIGPIPE early in the startup process so that threads writing to TLS
  // sockets do not crash when writing to a closed socket. See KUDU-1910.
  // IgnoreSigPipe();

  // TODO: support minidump
  // For minidump support. Must be called before logging threads started.
  // CHECK_OK(BlockSigUSR1());

  if (FLAGS_log_async) {
    EnableAsyncLogging();
  }

  logging_initialized = true;
}

}  // namespace osp
