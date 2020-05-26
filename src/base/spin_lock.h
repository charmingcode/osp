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
 https://github.com/facebook/rocksdb/blob/master/util/mutexlock.h

 */

#include "absl/base/internal/spinlock.h"

namespace osp {

// SpinLock has very low overhead for low-contention cases.  Method names
// are chosen so you can use std::unique_lock or std::lock_guard with it.
//
// class SpinLock {
//  public:
//   SpinLock() : locked_(false) {}

//   bool try_lock() {
//     auto currently_locked = locked_.load(std::memory_order_relaxed);
//     return !currently_locked &&
//            locked_.compare_exchange_weak(currently_locked, true,
//                                          std::memory_order_acquire,
//                                          std::memory_order_relaxed);
//   }

//   void lock() {
//     for (size_t tries = 0;; ++tries) {
//       if (try_lock()) {
//         // success
//         break;
//       }
//       port::AsmVolatilePause();
//       if (tries > 100) {
//         std::this_thread::yield();
//       }
//     }
//   }

//   void unlock() { locked_.store(false, std::memory_order_release); }

//  private:
//   std::atomic<bool> locked_;
// };

// NOTE: SpinLock the atomic-version, now we use the absl-version below
class ABSL_LOCKABLE SpinLock {
 public:
  SpinLock() = default;

  bool try_lock() ABSL_EXCLUSIVE_TRYLOCK_FUNCTION(true) {
    return lock_.TryLock();
  }
  void lock() ABSL_EXCLUSIVE_LOCK_FUNCTION() { lock_.Lock(); }
  void unlock() ABSL_UNLOCK_FUNCTION() { lock_.Unlock(); }

 private:
  absl::base_internal::SpinLock lock_;
};

}  // namespace osp