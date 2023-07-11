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

    void buildInorder(vector<TreeNode *> &inorder_list, TreeNode *root) {
        if (!root) return;
        buildInorder(inorder_list, root->left);
        inorder_list.push_back(root);
        buildInorder(inorder_list, root->right);
    }

    void buildPreorder(vector<TreeNode *> &preorder_list, TreeNode *root) {
        if (!root) return;
        preorder_list.push_back(root);
        buildPreorder(preorder_list, root->left);
        buildPreorder(preorder_list, root->right);
    }

    bool isSubStructure(TreeNode* A, TreeNode* B) {
        if (!A || !B) return false;
        /*
         *1. 先确定 B 的先序遍历集合和中序遍历集合
         *2.1.0 对 A 进行先序遍历
            1.1 如果 node->val == preorder_list[i]->val; i++
            1.2 如果 node->val != preorder_list[i]->val; i = 0; from_node = node
            1.3 如果 i == preorder_list.size(); i = -1
         * */
        vector<TreeNode *> a_pre, a_in, b_pre, b_in;
        buildPreorder(a_pre, A);
        buildInorder(a_in, A);
        buildPreorder(b_pre, B);
        buildInorder(b_in, B);
        int m = a_pre.size();
        int n = b_pre.size();
        if (m < n) return false;
        vector<int> a_pre_sub_idx_list;
        queue<int> in_temp;

        // 遍历 a 的先序数组
        // 找到所有可以当起点的索引
        for (int i = 0; i < m - n + 1; ++i) {
            if (a_pre[i]->val == b_pre[0]->val) {
                in_temp.push(i);
            }
        }
        int a_head;
        while (in_temp.size() > 0) {
            a_head = in_temp.front();
            in_temp.pop();
            for (int i = a_head; i < a_head + n; ++i) {
                TreeNode *cur_b = b_pre[i - a_head];
                TreeNode *cur_a = a_pre[i];
                if (cur_a->val == cur_b->val) {
                    if (n == 1) return true;
                    if (i == a_head + n - 1) {
                        // 全部相等, 记录下子集, 继续找下一个子集
                        a_pre_sub_idx_list.push_back(a_head);
                    }
                } else {
                    break;
                }
            }
        }

        // 检查得到的子集的中序集合是否跟in_b一致
        //   1. 先生成b中序集合的hash表，[node] = idx
        //   2. 生成a中序集合的hash表，[node] = idx
        //   3. 遍历找到的a先序集合
        //   4. i 为递增索引， b[i] -> [bnode] -> idx
        //   5. i 为递增索引， a[i] -> [anode] -> idx
        //   6. idx_b[i]-idx_b[i-1] == idx_a[i]-idx_a[i-1] 如果不等则退出，遍历结束则返回true

        unordered_map<TreeNode*, int> a_map;
        unordered_map<TreeNode*, int> b_map;
        printf("output A:\n");
        for (int i = 0; i < m; ++i) {
            a_map[a_in[i]] = i;
            printf("%d, %d\n", a_pre[i]->val, a_in[i]->val);
        }
        printf("output B:\n");
        for (int i = 0; i < n; ++i) {
            b_map[b_in[i]] = i;
            printf("%d, %d\n", b_pre[i]->val, b_in[i]->val);
        }
        int sub_num = a_pre_sub_idx_list.size();
        for (int i = 0; i < sub_num; ++i) {
            int a_head = a_pre_sub_idx_list[i];
            int a_idx_0 = a_map[a_pre[a_head]];
            int b_idx_0 = b_map[b_pre[0]];
            bool ret = true;
            for (int j = 1; j < n; ++j) {
                int a_idx = a_map[a_pre[a_head + j]] - a_idx_0;
                int b_idx = b_map[b_pre[j]] - b_idx_0;
                if (a_idx != b_idx) {
                    ret = false;
                    break;
                }
            }
            if (ret) return true;
        }

        return false;
    }
};

#endif
