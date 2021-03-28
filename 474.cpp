#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory.h>

using namespace std;

/*
题目：
给你一个二进制字符串数组 strs 和两个整数 m 和 n 。

请你找出并返回 strs 的最大子集的大小，该子集中 最多 有 m 个 0 和 n 个 1 。

如果 x 的所有元素也是 y 的元素，集合 x 是集合 y 的 子集
*/

class Solution {
public:
    // m -> 0的个数； n -> 1的个数
    int findMaxForm(vector<string> &strs, int m, int n) {
        // 初始化
        int **d = new int *[m + 1];
        for (int i = 0; i < m + 1; i++) {
            d[i] = new int[n + 1]{0};
            //memset(d[i], 0, sizeof(int) * (n + 1)); // 替换前面的所有字符为0，即格式化
        }
        int *cnt = new int[2];
        for (string str : strs) {
            Get(str, cnt); // 装进背包
            // 从后往前面装 i为0的个数,j为1的个数，不大于m,n就算满足条件
            for (int i = m; i >= cnt[0]; --i) {
                for (int j = n; j >= cnt[1]; --j) {
                    // 找到该字符串与前一个字符串是实现的相加
                    d[i][j] = max(d[i][j], 1 + d[i - cnt[0]][j - cnt[1]]);
                }
            }
        }
        return d[m][n];
    }

    // 计算0和1
    void Get(string &str, int *cnt) {
        memset(cnt, 0, sizeof(int) * 2);
        int n = str.size();
        for (int i = 0; i < n; i++) {
            ++cnt[str[i] - '0']; // '1' -'0' -> 1 ; '0' - '0' -> 0
        }
    }
};
