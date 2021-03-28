#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<bool> prefixesDivBy5(vector<int> &A) {
        int now = 0;
        vector<bool> res;
        for (int i:A) {
            now = ((now << 1) + i)%5;
            if (now  == 0) {
                res.emplace_back(true);
            } else {
                res.emplace_back(false);
            }
        }
        return res;
    }
};
