// 面试题 04.06. 后继者
//
// 设计一个算法，找出二叉搜索树中指定节点的“下一个”节点（也即中序后继）。
//
// 如果指定节点没有对应的“下一个”节点，则返回null。
//
// 示例 1:
//
// 输入: root = [2,1,3], p = 1
//
//   2
//  / \
// 1   3
//
// 输出: 2
// 示例 2:
//
// 输入: root = [5,3,6,2,4,null,null,1], p = 6
//
//       5
//      / \
//     3   6
//    / \
//   2   4
//  /
// 1
//
// 输出: null

#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

class TreeNode {
    public:
        TreeNode *left, *right;
        int val;
        TreeNode() : left(nullptr), right(nullptr), val(0) {
        }
        TreeNode(int _val) : left(nullptr), right(nullptr), val(_val) {
        }
};

const vector<string> explode(const string& s, const char& c)
{
    string buff{""};
    vector<string> v;

    for(auto n:s)
    {
        if(n != c) buff+=n; else
            if(n == c && buff != "") { v.push_back(buff); buff = ""; }
    }
    if(buff != "") v.push_back(buff);

    return v;
}

TreeNode *fetchInput(int *p) {
    string s;
    getline(cin, s);
    cin>>*p;
    TreeNode *root = NULL;
    if (s.size()) {
        vector<string> input{explode(s, ',')};
        root = new TreeNode();
        root->val = stoi(input[0]);
        queue<TreeNode *> q;
        q.push(root);
        size_t i = 1;
        while (i < input.size() && !q.empty()) {
            TreeNode *node = q.front();
            q.pop();
            if (input[i] != "null") {
                node->left = new TreeNode(stoi(input[i]));
                q.push(node->left);
            }
            if (++i >= input.size()) break;
            if (input[i] != "null") {
                node->right = new TreeNode(stoi(input[i]));
                q.push(node->right);
            }
            i++;
        }
    }
    return root;
}

/*
 * 1. main_loop 搜索节点
 * 2. if (root == node) return root->right
 *    if (root->left == node) return root->left->right? root->left->right: root;
 *    if (root->right == node) return root->right->right;
 * */
TreeNode *found = nullptr;
TreeNode *ans   = nullptr;
void search(TreeNode *root, int p) {
    if (!root) return;
    if (ans) return;
    search(root->left, p);
    if (!found) {
        if (root->val == p) {
            found = root;
        }
    } else {
        if (!ans) {
            ans = root;
        }
        return;
    }
    search(root->right, p);
}

int main(void)
{
    int p;
    TreeNode *root = fetchInput(&p);
    if (!root) exit(1);
    search(root, p);
    if (ans) {
        cout<<ans<<" "<<ans->val<<endl;
    } else {
        cout<<"null"<<endl;
    }
    return 0;
}

