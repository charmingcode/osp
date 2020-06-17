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
给定一个整数数组 nums 和一个目标值 target，请你在该数组中找出和为目标值的那 两个 整数，并返回他们的数组下标。

你可以假设每种输入只会对应一个答案。但是，数组中同一个元素不能使用两遍。


示例:

给定 nums = [2, 7, 11, 15], target = 9

因为 nums[0] + nums[1] = 2 + 7 = 9
所以返回 [0, 1]

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/two-sum
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

class Solution {
public:
    std::vector<int> TwoSum(std::vector<int>& nums, int target) {
        // key = the needed paired value, value = the paired value pos.
        std::map<int, int> to_pair;
        for (int i = 0; i < nums.size(); ++i) {
            if (to_pair.count(nums[i]) > 0) {
                return {to_pair[nums[i]], i};
            } else {
                to_pair[ target - nums[i] ] = i;
            }
        }
        return {};
    }
};

TEST(Solution, TwoSum) {
    Solution solution;
    std::vector<int> nums = {1,2,3};
    std::vector<int> expected_nums = {};
    EXPECT_EQ(solution.TwoSum(nums, 10), expected_nums);
    expected_nums = {0 ,1};
    EXPECT_EQ(solution.TwoSum(nums, 3), expected_nums);
}