// 请实现一个函数按照之字形顺序打印二叉树，即第一行按照从左到右的顺序打印，第二层按照从右到左的顺序打印，第三行再按照从左到右的顺序打印，其他行以此类推。
//
// 例如:
// 给定二叉树: [3,9,20,null,null,15,7],
//
//     3
//    / \
//   9  20
//     /  \
//    15   7
// 返回其层次遍历结果：
//
// [
//   [3],
//   [20,9],
//   [15,7]
// ]
//
//
// 提示：
//
// 节点总数 <= 1000

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
    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    };
    vector<vector<int>> levelOrder(TreeNode* root) {
        if (!root) return {};
        queue<TreeNode *> q;
        vector<vector<int>> ans;
        q.push(root);
        int overturn = 0;
        int i;
        auto fun = [&q](int i, vector<int> &temp){
            TreeNode *cur = q.front();
            q.pop();
            temp[i] = cur->val;
            if (cur->left) {q.push(cur->left)};
            if (cur->right) {q.push(cur->right)};
        };
        while (q.size()) {
            int n = q.size();
            vector<int> temp(n);
            if (overturn++) {
                for (i = n - 1; i >= 0; --i) {
                    fun(i, temp);
                }
            } else {
                for (i = 0; i < n; ++i) {
                    fun(i, temp);
                }
            }
            ans.push_back(temp);
            overturn &= 1;
        }
        return ans;
    }
};
