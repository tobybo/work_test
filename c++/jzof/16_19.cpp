// 面试题 16.19. 水域大小
//
// 你有一个用于表示一片土地的整数矩阵land，
// 该矩阵中每个点的值代表对应地点的海拔高度。
// 若值为0则表示水域。由垂直、水平或对角连接的水域为池塘。
// 池塘的大小是指相连接的水域的个数。编写一个方法来计算矩阵中所有池塘的大小，返回值需要从小到大排序。
//
// 示例：
//
// 输入：
// [
//   [0,2,1,0],
//   [0,1,0,1],
//   [1,1,0,1],
//   [0,1,0,1]
// ]
// 输出： [1,2,4]
// 提示：
//
// 0 < len(land) <= 1000
// 0 < len(land[i]) <= 1000

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const vector<int> explode(const string& s, const char& c)
{
    string buff{""};
    vector<int> v;

    for(auto n:s)
    {
        if(n != c) buff+=n; else
            if(n == c && buff != "") { v.push_back(stoi(buff)); buff = ""; }
    }
    if(buff != "") v.push_back(stoi(buff));

    return v;
}

vector<vector<int>> fetchInput() {
    int m;
    cin>>m;
    cin.ignore();
    vector<vector<int>> nums;
    for (int i = 0; i < m; ++i) {
        string s;
        getline(cin, s);
        vector<int> temp{explode(s, ',')};
        nums.push_back(temp);
        // cout<<endl;
        // cout<<s<<endl;
        // for (int val: temp) {
        //     cout<<val<<" ";
        // }
        // cout<<endl;
    }
    return nums;
}

void doSubSolution(vector<vector<int>> &nums, size_t x, size_t y, int *count, vector<vector<bool>> &vis) {
    if (y < 0 || y >= nums.size() || x < 0 || x >= nums[0].size()) return;
    if (vis[y][x] || nums[y][x]) return;
    vis[y][x] = true;
    (*count)++;
    //cout<<"count: "<<*count<<", x: "<<x<<", y: "<<y<<", val: "<<nums[y][x]<<endl;
    doSubSolution(nums, x + 1, y, count, vis);
    doSubSolution(nums, x, y + 1, count, vis);
    doSubSolution(nums, x + 1, y + 1, count, vis);
    doSubSolution(nums, x - 1, y + 1, count, vis);
    doSubSolution(nums, x + 1, y - 1, count, vis);
    doSubSolution(nums, x - 1, y - 1, count, vis);
    doSubSolution(nums, x, y - 1, count, vis);
    doSubSolution(nums, x - 1, y, count, vis);
}

vector<int> solution(vector<vector<int>> &nums) {
    vector<int> ans;

    do {
        size_t m,n;
        m = nums.size();
        if (!m) break;
        n = nums[0].size();
        if (!n) break;
        int count;
        vector<vector<bool>> vis(m, vector<bool>(n, 0));
        for (size_t y = 0; y < m; ++y) {
            for (size_t x = 0; x < n; ++x) {
                count = 0;
                doSubSolution(nums, x, y, &count, vis);
                if (count) {
                    ans.push_back(count);
                }
            }
        }
    } while(0);

    if (ans.size()) {
        sort(ans.begin(), ans.end());
    }
    return ans;
}

int main(void)
{
    vector<vector<int>> nums = fetchInput();
    vector<int> ans = solution(nums);
    for (auto v: ans) {
        cout<<v<<" ";
    }
    cout<<endl;
    return 0;
}





