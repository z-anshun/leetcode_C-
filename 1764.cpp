#include "iostream"
#include "vector"
#include "algorithm"

using namespace std;

class Solution {
public:
    bool canChoose(vector<vector<int>> &groups, vector<int> &nums) {
        int n = nums.size(), cur = 0;
        for (int i = 0; i < n; i++) {
            // 如果第一个满足。且长度足够
            if (nums[i] == groups[cur][0] && n - i >= groups[cur].size()) {
                vector<int> tmp(nums.begin() + i, nums.begin() + i + groups[cur].size());
                if (tmp == groups[cur]) {
                    i += groups[cur].size() - 1;
                    cur++;
                }
                if (cur >= groups.size())return true;
            }
        }
        return false;
    }

};

