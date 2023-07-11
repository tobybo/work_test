// 输入两棵二叉树A和B，判断B是不是A的子结构。(约定空树不是任意一个树的子结构)
//
// B是A的子结构， 即 A中有出现和B相同的结构和节点值。
//
// 例如:
// 给定的树 A:
//
//      3
//
//     / \
//
//    4   5
//
//   / \
//
//  1   2
// 给定的树 B：
//
//    4
//
//   /
//
//  1
// 返回 true，因为 B 与 A 的一个子树拥有相同的结构和节点值。
//
// 示例 1：
//
// 输入：A = [1,2,3], B = [3,1]
// 输出：false
// 示例 2：
//
// 输入：A = [3,4,5,1,2], B = [4,1]
// 输出：true
// 限制：
//
// 0 <= 节点个数 <= 10000

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

#ifndef _26_h_
#define _26_h_

#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <map>
#include <unordered_map>
using namespace std;

class Solution {
public:
	struct TreeNode {
		int val;
		TreeNode *left;
		TreeNode *right;
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
	};

    void preorderSearch(TreeNode *root, queue<TreeNode *> &q, int b_root_val) {
        if (!root) return;
        if (root->val == b_root_val) {
            q.push(root);
        }
        preorderSearch(root->left, q, b_root_val);
        preorderSearch(root->right, q, b_root_val);
    }

    bool preorderCheck(TreeNode *root, TreeNode *check) {
        if (!root) return true;
        if (!check) return false;
        if (root->val != check->val) return false;
        return preorderCheck(root->left, check->left) &&
                preorderCheck(root->right, check->right);
    }

    bool isSubStructure(TreeNode* A, TreeNode* B) {
        if (!A || !B) return false;
        /*
         *1. 先遍历 A 找到跟 B root 节点值相同的节点集合
         *2. 先序遍历 B, 检查 B 具有的所有子节点值是否在 A 中依次出现
         * */
        queue<TreeNode *> q;
        preorderSearch(A, q, B->val);
        while (q.size() > 0) {
            TreeNode *root = q.front();
            q.pop();
            if (preorderCheck(B, root)) {
                return true;
            }
        }
        return false;
    }
};

#endif
