//============================================================================
// Name        : TwoSum.cpp
// Author      : Aref Abedjooy
// Version     : 1.0
// Copyright   : Copyright (c) 2022, Aref Abedjooy. No Rights Reserved.
// Description : https://leetcode.com/problems/two-sum/ 
//============================================================================
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

/*

Algorithm:

It turns out we can do it in one-pass. 
While we are iterating and inserting elements into the hash table,
we also look back to check if current element's complement already exists
in the hash table. If it exists, 
we have found a solution and return the indices immediately

*/

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> myMap;
        
        for(int i =0; i<nums.size();i++){
            if(myMap.find(target-nums[i]) != myMap.end()){
                return {i,myMap[target-nums[i]]};
            }
            myMap[nums[i]] = i;
        }
        
        return {};
    }
};

/*
Complexity Analysis:

Time complexity: O(n). 
                 We traverse the list containing n elements only once. 
                 Each lookup in the table costs only O(1) time.

Space complexity: O(n). 
                  The extra space required depends on the number of items stored 
                  in the hash table, which stores at most n elements


*/


int main(){
    Solution *solution = new Solution();
    vector<int> nums = {2,7,11,15};
    int target = 9;
    vector<int> res = solution->twoSum(nums,target);
    for(int i=0; i<res.size(); i++){
        cout << res[i] << endl;
    }

}