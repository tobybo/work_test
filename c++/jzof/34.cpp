// 给你二叉树的根节点 root 和一个整数目标和 targetSum ，找出所有 从根节点到叶子节点 路径总和等于给定目标和的路径。
//
// 叶子节点 是指没有子节点的节点。

// 输入：root = [5,4,8,11,null,13,4,7,2,null,null,5,1], targetSum = 22
// 输出：[[5,4,11,2],[5,8,4,5]]

// 树中节点总数在范围 [0, 5000] 内
// -1000 <= Node.val <= 1000
// -1000 <= targetSum <= 1000

#include <iostream>
#include <string>
#include <vector>
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

void findRoad(TreeNode *root, vector<vector<int>> &ans, vector<int> &road, int target, int sum) {
    sum += root->val;
    road.push_back(root->val);
    if (!root->left && !root->right) {
        if (sum == target) {
            ans.push_back(road);
        }
    } else {
        if (root->left) { findRoad(root->left, ans, road, target, sum);}
        if (root->right) { findRoad(root->right, ans, road, target, sum);}
    }
    sum -= root->val;
    road.pop_back();
}

int main() {
    string s;
    int target;
    cout<<"请输入目标和: ";
    cin>>target;
    cin.ignore();
    cout<<"请输入二叉树: ";
    getline(cin, s);
    cout<<"输入为: "<<s<<endl;
    vector<string> input{explode(s, ',')};
    TreeNode *root = buildRoot(input);
    if (!root) return 0;
    vector<vector<int>> ans;
    vector<int> road;
    int sum = 0;
    findRoad(root, ans, road, target, sum);
    cout<<"输出:"<<endl;
    for (int i = 0; i < ans.size(); ++i) {
        cout<<"[";
        for (int j = 0; j < ans[0].size(); ++j) {
            cout<<ans[i][j];
            if (j != ans[0].size() - 1) {
                cout<<",";
            }
        }
        cout<<"]"<<endl;
    }
    return 0;
}



