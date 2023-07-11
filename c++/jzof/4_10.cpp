// 面试题 04.10. 检查子树
//
// 检查子树。你有两棵非常大的二叉树：T1，有几万个节点；T2，有几万个节点。设计一个算法，判断 T2 是否为 T1 的子树。
//
// 如果 T1 有这么一个节点 n，其子树与 T2 一模一样，则 T2 为 T1 的子树，也就是说，从节点 n 处把树砍断，得到的树与 T2 完全相同。
//
// 注意：此题相对书上原题略有改动。
//
// 示例1:
//
//  输入：t1 = [1, 2, 3], t2 = [2]
//  输出：true
// 示例2:
//
//  输入：t1 = [1, null, 2, 4], t2 = [3, 2]
//  输出：false
// 提示：
//
// 树的节点数目范围为[0, 20000]。

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

const vector<string> explode(const string& s, const char& c)
{
    string buff{""};
    vector<string> v;

    for(auto n:s)
    {
        if(n != c && n != ' ') buff+=n; else
            if(n == c && buff != "") { v.push_back(buff); buff = ""; }
    }
    if(buff != "") v.push_back(buff);

    return v;
}

class TreeNode {
    public:
        int val;
        TreeNode *left = nullptr;
        TreeNode *right = nullptr;
        TreeNode(int _val): val(_val) {}
        void build(vector<string> &input) {
            queue<TreeNode *> q;
            this->val = stoi(input[0]);
            q.push(this);
            size_t n = input.size();
            size_t i = 1;
            while (!q.empty() && i < n) {
                size_t num = q.size();
                for (size_t j = 0; j < num; ++j) {
                    TreeNode *curRoot = q.front();
                    q.pop();
                    if (input[i] != "null") {
                        curRoot->left = new TreeNode(stoi(input[i]));
                    }
                    if (++i == n) break;
                    if (input[i] != "null") {
                        curRoot->right = new TreeNode(stoi(input[i]));
                    }
                    if (++i == n) break;
                }
            }
        }
};

queue<TreeNode *> next_q;

bool preMatch(TreeNode *t1, TreeNode *t2) {
    if (!t1 && !t2) return true;
    if (!t1 || !t2) return false;
    if (t1->val != t2->val) return false;
    return preMatch(t1->left, t2->left) && preMatch(t1->right, t2->right);
}

void preFind(TreeNode *t1, int t2_root_val) {
    if (!t1) return;
    if (t1->val == t2_root_val) {
        next_q.push(t1);
    }
    preFind(t1->left, t2_root_val);
    preFind(t1->right, t2_root_val);
}

int main(void)
{
    string s1, s2;
    getline(cin, s1);
    getline(cin, s2);
    vector<string> t1{explode(s1, ',')};
    vector<string> t2{explode(s2, ',')};
    bool ans = true;
    if (t1.size() && t2.size() && t1.size() >= t2.size()) {
        TreeNode *root1 = new TreeNode(0);
        TreeNode *root2 = new TreeNode(0);
        root1->build(t1);
        root2->build(t2);
        preFind(root1, root2->val);
        ans = false;
        while (!next_q.empty()) {
            TreeNode *match_t1 = next_q.front();
            next_q.pop();
            if (preMatch(match_t1, root2)) {
                ans = true;
                break;
            }
        }
    }
    cout<<(ans ? "true" : "false")<<endl;
    return 0;
}
