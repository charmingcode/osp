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
   Created on: Jun 18, 2020
 */

#include <glog/logging.h>
#include <gtest/gtest.h>
#include <map>
#include <vector>

/*
Given a string, find the length of the longest substring without repeating characters.

Example 1:

Input: "abcabcbb"
Output: 3 
Explanation: The answer is "abc", with the length of 3. 
Example 2:

Input: "bbbbb"
Output: 1
Explanation: The answer is "b", with the length of 1.
Example 3:

Input: "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3. 
             Note that the answer must be a substring, "pwke" is a subsequence and not a substring.

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/longest-substring-without-repeating-characters
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

class Solution {
 public:
  int lengthOfLongestSubstring(std::string s) {
    // the pos indicates the 'a'-'z' whether exists
    // the val indicates the pos of the character in the s, begin from 1
    int bitmap[255] = {0};

    int max_start_pos = 0;
    int max_len = 0;
    int cur_start_pos = 0;
    int cur_len = 0;

    for (int i = 0; i < s.length(); ++i) {
      int pos = s.at(i) - 0x00;
      if (bitmap[pos] == 0) {
        bitmap[pos] = i + 1;
        cur_len++;
      } else {
        if (cur_len > max_len) {
          max_len = cur_len;
          max_start_pos = cur_start_pos;
        }

        LOG(INFO) << "substring without repeating characters is "
                  << s.substr(cur_start_pos, cur_len)
                  << ", cur_start_pos = " << cur_start_pos;

        // save the same character pos + 1, becase maybe reset below
        int new_cur_start_pos = bitmap[pos];

        // reset bitmap from old_start_pos to the new_start_pos
        for (int j = cur_start_pos; j < bitmap[pos]; j++) {
          int pos2 = s.at(j) - 0x00;
          bitmap[pos2] = 0;
        }

        // update the new str start pos, from the same character pos + 1
        cur_start_pos = new_cur_start_pos;
        // update the same character pos
        bitmap[pos] = i + 1;
        // update the new str tmp len
        cur_len = i - cur_start_pos + 1;
      }
    }

    // if the last character is active len, need check the cur_len
    if (max_len < cur_len) {
      max_len = cur_len;
    }

    LOG(INFO) << "longest substring without repeating characters is "
              << s.substr(max_start_pos, max_len)
              << ", max_start_pos = " << max_start_pos;
    return max_len;
  }
};

TEST(Solution, basic) {
  Solution solution;
  EXPECT_EQ(solution.lengthOfLongestSubstring("aaa"), 1);
  EXPECT_EQ(solution.lengthOfLongestSubstring("abcabcbb"), 3);
  EXPECT_EQ(solution.lengthOfLongestSubstring("pwwkew"), 3);
  EXPECT_EQ(solution.lengthOfLongestSubstring(" "), 1);
  EXPECT_EQ(solution.lengthOfLongestSubstring("aab"), 2);
  EXPECT_EQ(solution.lengthOfLongestSubstring("dvdf"), 3);
  EXPECT_EQ(solution.lengthOfLongestSubstring("abba"), 2);
  EXPECT_EQ(
      solution.lengthOfLongestSubstring(
          "hijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789hijklmnopqrst"
          "uvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789hijklmnopqrstuvwxyzABCDEFG"
          "HIJKLMNOPQRSTUVWXYZ0123456789hijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRST"
          "UVWXYZ0123456789hijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456"
          "789hijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"),
      55);
}