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
   Created on: Jun 17, 2020
 */

#include <map>
#include <vector>
#include <gtest/gtest.h>

/*
You are given two non-empty linked lists representing two non-negative integers. The digits are stored in reverse order and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.

You may assume the two numbers do not contain any leading zero, except the number 0 itself.

Example:

Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 0 -> 8
Explanation: 342 + 465 = 807.

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/add-two-numbers
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class TestHelp {
public:
    // create the list by the input 'nums'
    static ListNode* GenList(std::vector<int> nums) {
        ListNode* result = nullptr;
        ListNode* ret = nullptr;
        for(size_t i = 0; i < nums.size(); i++) {
            if(!result) {
              result = new ListNode(nums[i]);
              ret = result;
            } else {
              result->next = new ListNode(nums[i]);
              result = result->next;
            }
        }
        return ret;
    }

    static std::vector<int> Convert(ListNode* list) {
        std::vector<int> result;
        while(list != nullptr) {
            result.push_back(list->val);
            list = list->next;
        }
        return result;
    }
};

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* result = nullptr;
        ListNode* ret = nullptr;
        int add_flag = 0;
        while (l1 != nullptr || l2 != nullptr || add_flag == 1)
        {
            if(!result) {
              result = new ListNode(0);
              ret = result;
            } else {
              result->next = new ListNode(0);
              result = result->next;
            }
                
            if(l1) {
                result->val += l1->val;
                l1 = l1->next;
            }

            if(l2) {
                result->val += l2->val;
                l2 = l2->next;
            }

            if(add_flag) {
                result->val +=1;
                add_flag = 0;
            }

            if(result->val/10 > 0) {
                result->val = result->val%10;
                add_flag =1;
            }
        }

        return ret;
    }
};

TEST(Solution, basic) {
    Solution solution;
    ListNode* l1 = TestHelp::GenList({1, 2, 3});
    ListNode* l2 = TestHelp::GenList({1, 2, 3});
    std::vector<int> expected_result = {2, 4, 6};
    EXPECT_EQ(TestHelp::Convert(solution.addTwoNumbers(l1, l2)), expected_result);

    l1 = TestHelp::GenList({1, 2, 3});
    l2 = TestHelp::GenList({3, 5});
    expected_result = {4, 7, 3};
    EXPECT_EQ(TestHelp::Convert(solution.addTwoNumbers(l1, l2)), expected_result);
}