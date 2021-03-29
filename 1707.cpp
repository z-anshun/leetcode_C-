#include "iostream"
#include "vector"
#include "sstream"

using namespace std;

// 问题：
/* 给你一个由非负整数组成的数组 nums 。另有一个查询数组 queries ，其中 queries[i] = [xi, mi] 。

第 i 个查询的答案是 xi 和任何 nums 数组中不超过 mi 的元素按位异或（XOR）得到的最大值。
换句话说，答案是 max(nums[j] XOR xi) ，其中所有 j 均满足 nums[j] <= mi 。
如果 nums 中的所有元素都大于 mi，最终答案就是 -1 。

返回一个整数数组 answer 作为查询的答案，
其中 answer.length == queries.length 且 answer[i] 是第 i 个查询的答案。
*/

struct TrieNode {
    int lo = INT_MAX;
    TrieNode *children[2]{};
};

class Solution {
public:
    vector<int> maximizeXor(vector<int> &nums, vector<vector<int>> &queries) {
        // 建立字典树
        TrieNode *root = new TrieNode();
        for (int num:nums) {
            TrieNode *p = root;
            // 最多不过30位
            for (int i = 30; i >= 0; --i) {
                // 判断下一个是0还是1
                // 若 num=1101 i=2 1101&0100=1
                int nxt = (num & (1 << i)) ? 1 : 0;
                if (!p->children[nxt]) {
                    // 如果为nullptr
                    p->children[nxt] = new TrieNode;
                }
                p = p->children[nxt];
                p->lo = min(p->lo, num);
            }
        }

        vector<int> answer(0);
        int max = -1;
        for (auto arr:queries) {
            int x = arr[0], limit = arr[1];
            int ans = 0;
            TrieNode *p = root;
            for (int i = 30; i >= 0; --i) {
                if (x & (1 << i)) {
                    // 如果当前位为1
                    if (p->children[0]) {
                        // 如果含有0节点,这里不用管limit，因为x后面还有位数，即比他大
                        p = p->children[0];
                        ans ^= (1 << i);
                    } else if (!p->children[1] || (p->children[1]->lo > limit)) {
                        // 获取当前的为1的num节点大于了 limit
                        answer.emplace_back(-1);
                        break;
                    } else {
                        p = p->children[1];
                    }
                } else {
                    // 如果当前位为0
                    if (p->children[1] && p->children[1]->lo <= limit) {
                        // 如果当前节点有为1的孩子节点，且满足条件，这样就需要判断
                        p = p->children[1];
                        ans ^= (1 << i); // 对该位进行异或运算
                    } else if (!p->children[0]) {
                        // 没有0，也没有1
                        answer.emplace_back(-1);
                        break;
                    } else {
                        p = p->children[0];
                    }
                }
                if (i == 0) {
                    // 加入
                    answer.emplace_back(ans);
                }
            }
        }
        return answer;
    }
};

