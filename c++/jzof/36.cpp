// 输入一棵二叉搜索树，将该二叉搜索树转换成一个排序的循环双向链表。要求不能创建任何新的节点，只能调整树中节点指针的指向。

// 我们希望将这个二叉搜索树转化为双向循环链表。链表中的每个节点都有一个前驱和后继指针。对于双向循环链表，第一个节点的前驱是最后一个节点，最后一个节点的后继是第一个节点。

// 特别地，我们希望可以就地完成转换操作。当转化完成以后，树中节点的左指针需要指向前驱，树中节点的右指针需要指向后继。还需要返回链表中的第一个节点的指针。

#include <iostream>
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
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode(int _val):val(_val),left(NULL),right(NULL){}
};

TreeNode *buildRoot(vector<string> &input) {
    int n = input.size();
    if (!n) return NULL;
    TreeNode *root = new TreeNode(stoi(input[0]));
    queue<TreeNode*> stk;
    stk.push(root);
    TreeNode *temp_root;
    int p = 1;
    while (!stk.empty() && p < n) {
        for (int i = 0; i < stk.size(); ++i) {
            temp_root = stk.front();
            stk.pop();
            if (p >= n) break;
            if (input[p] == "null") {
                p++;
            } else {
                temp_root->left = new TreeNode(stoi(input[p++]));
                stk.push(temp_root->left);
            }
            if (p >= n) break;
            if (input[p] == "null") {
                p++;
            } else {
                temp_root->right = new TreeNode(stoi(input[p++]));
                stk.push(temp_root->right);
            }
        }
    }
    return root;
}

TreeNode *inorderSearch(TreeNode *root);

TreeNode *inorderSearchEx(TreeNode *root) {
    if (root->right) {
        return inorderSearchEx(root->right);
    }
    return root;
}

TreeNode *inorderSearch(TreeNode *root) {
    if (root->left) {
        return inorderSearch(root->left);
    }
    return root;
}

TreeNode *getHead(TreeNode *root) {
    TreeNode *head = root;
    if (root->left) head = getHead(root->left);
    TreeNode *tail = root;
    if (root->right) tail = (root->right);
    head->left = tail;
    tail->right = head;
    return head;
}

int main() {
    string s;
    cin>>s;
    vector<string> input{explode(s, ',')};
    TreeNode *root = buildRoot(input);
    if (!root) return 0;

    TreeNode *cur = head;
    do {
        cout<<cur->val<<" ";
        cur = cur->right;
    } while (cur != head);
    return 0;
}
