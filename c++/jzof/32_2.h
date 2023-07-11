// 从上到下按层打印二叉树，同一层的节点按从左到右的顺序打印，每一层打印到一行。
//
//
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
//   [9,20],
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
        while (q.size()) {
            int n = q.size();
            vector<int> temp(n);
            for (int i = 0; i < n; ++i) {
                TreeNode *cur = q.front();
                q.pop();
                temp[i] = cur->val;
                if (cur->left) {
                    q.push(cur->left);
                }
                if (cur->right) {
                    q.push(cur->right);
                }
            }
            ans.push_back(temp);
        }
        return ans;
    }
};
