#include "iostream"
#include "vector"

using namespace std;

// s是否为t的字串
class Solution {
public:
    // 贪心
    // 时间复杂度：O(n+m)
    bool isSubsequence(string s, string t) {
        int n = s.length(), m = t.length();
        int i = 0, j = 0;
        while (i < n && j < m) {
            if (s[i] == t[j]) {
                i++;
            }
            j++;
        }
        return i == n;
    }

    bool isSubsequenceByDy(string s, string t) {
        int n = s.length(), m = t.length();
        vector<vector<int>> f(m + 1, vector<int>(26, 0));

        for (int i = 0; i < 26; i++) {
            f[m][i] = m;
        }

        // 从后往前面记录
        for (int i = m - 1; i >= 0; i--) {
            for (int j = 0; j < 26; j++) {
                if (t[i] == j + 'a') {// 如果当前含有这个byte，就赋值
                    f[i][j] = i;
                } else {
                    f[i][j] = f[i + 1][j];// 往后面找,若没有就会为m
                }
            }
        }

        int add = 0;
        for (int i = 0; i < n; i++) {
            // 只要不等于m，就证明后面有这个字母
            if (f[add][s[i] - 'a'] == m) {
                return false;
            }
            // 往后移
            add = f[add][s[i] - 'a'] + 1;
        }
        return true;
    }
};
