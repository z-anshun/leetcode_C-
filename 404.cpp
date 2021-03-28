#include "iostream"
#include "vector"

using namespace std;


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    // TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// 计算给定二叉树的所有左叶子之和。

class Solution {
public:
    int sumOfLeftLeaves(TreeNode *root) {
        int nResults = 0;
        if (root == nullptr) {
            return nResults;
        }

        // 下一个左节点 无左右节点
        if (root->left != nullptr && root->left->left == nullptr && root->left->right == nullptr) {
            nResults += root->left->val;
            // 证明下一个就是左叶子节点，可以直接访问其右节点
            return nResults + sumOfLeftLeaves(root->right);
        }

        return sumOfLeftLeaves(root->left) + sumOfLeftLeaves(root->right) + nResults;
    }
};

