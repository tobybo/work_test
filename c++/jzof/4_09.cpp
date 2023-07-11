// 面试题 04.09. 二叉搜索树序列
//
// 从左向右遍历一个数组，通过不断将其中的元素插入树中可以逐步地生成一棵二叉搜索树。
//
// 给定一个由不同节点组成的二叉搜索树 root，输出所有可能生成此树的数组。
//
//
//
// 示例 1:
//
// 输入: root = [2,1,3]
// 输出: [[2,1,3],[2,3,1]]
// 解释: 数组 [2,1,3]、[2,3,1] 均可以通过从左向右遍历元素插入树中形成以下二叉搜索树
//        2
//       / \
//      1   3
// 示例 2:
//
// 输入: root = [4,1,null,null,3,2]
// 输出: [[4,1,3,2]]
//
//
// 提示：
//
// 二叉搜索树中的节点数在 [0, 1000] 的范围内
// 1 <= 节点值 <= 10^6
// 用例保证符合要求的数组数量不超过 5000

#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

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

class TreeNode {
    public:
    int val = 0;
    TreeNode *left = NULL;
    TreeNode *right = NULL;

    TreeNode(int _val):val(_val){}
    TreeNode(){}

    void buildTree(vector<string> &input) {
        queue<TreeNode *> q;
        q.push(this);
        size_t n = input.size();
        this->val = stoi(input[0]);
        int i = 1;
        while (i < n) {
            int step_num = q.size();
            for (int j = 0; j < step_num; ++j) {
                TreeNode *cur = q.front();
                q.pop();
                if (input[i] != "null") {
                    cur->left = new TreeNode(stoi(input[i]));
                    q.push(cur->left);
                }
                i++;
                if (i >= n) break;
                if (input[i] != "null") {
                    cur->right = new TreeNode(stoi(input[i]));
                    q.push(cur->right);
                }
                i++;
            }
        }
    }
};

vector<vector<int>> ans;

void bfs(deque<TreeNode *> &q, vector<int> &arr) {
    if (q.empty()) {
        ans.push_back(arr);
        return;
    }
    int n = q.size();
    int child_num;
    while (n--) {
        TreeNode *cur = q.front();
        q.pop_front();
        arr.push_back(cur->val);
        child_num = 0;
        if (cur->left) {
            child_num++;
            q.push_back(cur->left);
        }
        if (cur->right) {
            child_num++;
            q.push_back(cur->right);
        }
        bfs(q, arr);
        while (child_num--) {
            q.pop_back();
        }
        q.push_back(cur);
        arr.pop_back();
    }
}

int main() {
    string s;
    getline(cin, s);
    vector<string> input{explode(s, ',')};
    TreeNode *root = new TreeNode();
    root->buildTree(input);
    deque<TreeNode *> q;
    q.push_back(root);
    vector<int> arr;
    bfs(q, arr);
    for (auto inner: ans) {
        for (int val: inner) {
            cout<<val<<" ";
        }
        cout<<endl;
    }
    return 0;
}
