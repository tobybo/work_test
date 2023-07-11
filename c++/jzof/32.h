// 从上到下打印出二叉树的每个节点，同一层的节点按照从左到右的顺序打印。
//
// 例如:
// 给定二叉树: [3,9,20,null,null,15,7],
//
//     3
//    / \
//   9  20
//     /  \
//    15   7
// 返回：
//
// [3,9,20,15,7]
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
    vector<int> levelOrder(TreeNode* root) {
        if (!root) return {};
        vector<int> ans;
        queue<TreeNode *> q;
        q.push(root);
        while (q.size() > 0) {
            TreeNode *cur = q.front();
            q.pop();
            v.push_back(cur->val);
            if (cur->left) {
                q.push(cur->left);
            }
            if (cur->right) {
                q.push(cur->right);
            }
        }
        return ans;
    }
};
