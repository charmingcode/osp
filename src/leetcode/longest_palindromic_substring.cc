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
   Created on: Jun 20, 2020
 */

#include <glog/logging.h>
#include <gtest/gtest.h>
#include <map>
#include <vector>


#define MIN(a, b) ((a)<(b)?(a):(b))

class Solution {
public:
    int longestPalindrome(std::string s1, std::string s2) {
        int palindormic_len = 0;
        for (int i = 0; i < s1.length() && i < s2.length(); i++) {
            if(s1.at(s1.length() - 1 - i) == s2.at(i)) {
                palindormic_len++;
                continue;
            } else {
                break;
            }
        }
        return palindormic_len;
    };

    std::string longestPalindrome(std::string s) {
        std::string result;
        if(s.empty()) {
            return "";
        }

        if(s.length() == 1) {
            return s;
        }

        result = s.at(0);

        for (int cur = 0; cur < s.length()-1; ++cur) {
            int len = longestPalindrome(s.substr(0, cur+1), s.substr(cur+1, s.length()-(cur+1)));
            std::string str;
            if( len > 0 ) {
                str = s.substr(cur + 1 - len, len*2);
            }

            if(str.length() > result.length())
                result = str;

            if(cur > 0) {
                len =  longestPalindrome(s.substr(0, cur), s.substr(cur+1, s.length()-(cur+1)));
                if( len > 0 ) {
                    str = s.substr(cur - len, len*2+1);
                    if(str.length() > result.length())
                        result = str;
                 }
            }
        }
        return result;
    }
};

TEST(Solution, basic) {
  Solution solution;
  EXPECT_EQ(solution.longestPalindrome("babad"), "bab");
  EXPECT_EQ(solution.longestPalindrome("a"), "a");
  EXPECT_EQ(solution.longestPalindrome("aa"), "aa");
  EXPECT_EQ(solution.longestPalindrome("ccc"), "ccc");
}