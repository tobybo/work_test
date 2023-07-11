// 请实现一个函数，用来判断一棵二叉树是不是对称的。如果一棵二叉树和它的镜像一样，那么它是对称的。
//
// 例如，二叉树 [1,2,2,3,4,4,3] 是对称的。
//
//     1
//
//    / \
//
//   2   2
//
//  / \ / \
//
// 3  4 4  3
// 但是下面这个 [1,2,2,null,3,null,3] 则不是镜像对称的:
//
//     1
//
//    / \
//
//   2   2
//
//    \   \
//
//    3    3
//
//
//
// 示例 1：
//
// 输入：root = [1,2,2,3,4,4,3]
// 输出：true
// 示例 2：
//
// 输入：root = [1,2,2,null,3,null,3]
// 输出：false
//
//
// 限制：
//
// 0 <= 节点个数 <= 1000

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

class Solution {
public:
    void preorderOverturn(TreeNode *base, TreeNode *copy) {
        copy->val = base->val;
        if (base->right) {
            copy->left = new TreeNode(0);
            preorderOverturn(base->right, copy->left);
        }
        if (base->left) {
            copy->right = new TreeNode(0);
            preorderOverturn(base->left, copy->right);
        }

    }

    void preorderCheck(TreeNode *base, TreeNode *copy) {
        if (!base && !copy) return true;
        if (!base || !copy) return false;
        if (base->val != copy->val) return false;
        return preorderCheck(base->left, copy->left) && preorderCheck(base->right, copy->right);
    }

    void preorderDelete(TreeNode *root) {
        if (!root) return;
        TreeNode *left = root->left;
        TreeNode *right = root->right;
        delete(root);
        preorderDelete(left);
        preorderDelete(right);
    }

    bool isSymmetric(TreeNode* root) {
        if (!root) return false;
        TreeNode *copy = new TreeNode(0);
        preorderOverturn(root, copy);
        bool ans = preorderCheck(root, copy);
        preorderDelete(copy);
        return ans;
    }
};
