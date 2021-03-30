#include "iostream"
#include "vector"
#include "algorithm"

using namespace std;

// 贪心算法
// 因为 sum(A)=A[a1]+A[a2]+...+A[an],sum(B)=B(sum)-B[a1]-B[a2]-...-B[an]
// 所以 最优化A=A[i]+B[i]最大时，B同理
class Solution {
public:
    int stoneGameVI(vector<int> &aliceValues, vector<int> &bobValues) {
        vector<pair<int, int>> mp;
        int n = aliceValues.size();
        for (int i = 0; i < n; i++) {
            int dis = aliceValues[i] + bobValues[i];
            mp.emplace_back(dis, i);
        }
        sort(mp.begin(), mp.end());
        int sum1 = 0, sum2 = 0;
        for (int i = 0; i < n; i++) {
            cout << mp[i].first << endl;
            if (i % 2 == 0) {
                sum1 += aliceValues[mp[i].second];
            } else {
                sum2 += bobValues[mp[i].second];
            }
        }
        if (sum1 == sum2) {
            return 0;
        } else if (sum1 > sum2) {
            return 1;
        } else {
            return -1;
        }
    }
};
