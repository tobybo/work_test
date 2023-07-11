// 给定一个数组，包含从 1 到 N 所有的整数，但其中缺了两个数字。你能在 O(N) 时间内只用 O(1) 的空间找到它们吗？
//
// 以任意顺序返回这两个数字均可。
//
// 示例 1:
//
// 输入: [1]
// 输出: [2,3]
// 示例 2:
//
// 输入: [2,3]
// 输出: [1,4]
// 提示：
//
// nums.length <= 30000

#include <iostream>
#include <vector>
#include <string>

using namespace std;

void mySort(vector<int> &nums, int last, int i, int ans[]) {
    //cout<< "sort: "<< ans[0] << "," << ans[1] <<endl;
    int next_pos = nums[i] - 1;
    if (next_pos == i) return;
    if (i != last) {
        nums[i] = i + 1;
    }
    for (int j = 0; j < 2; ++j) {
        if (next_pos == ans[j]) {
            if (next_pos < nums.size()) {
                // 确认找到位置，设置为正确的值
                nums[next_pos] = next_pos + 1;
            }
            ans[j] = last; // [1,3] [0,3]
            //cout<< "修改: "<< ans[0] << "," << ans[1] <<endl;
            return;
        }
    }
    // 确认找到位置，设置为正确的值
    cout<<i<<","<<next_pos<<","<<nums.size()<<endl;
    mySort(nums, last, next_pos, ans);
}

int main() {
    vector<int> nums;
    string s;
    getline(cin, s);
    int n = s.size();
    int head = 0;
    for (int i = 0; i < n; ++i) {
        if (s[i] == ',') {
            nums.push_back(stoi(s.substr(head, i - head)));
            head = i + 1;
        } else if (i == n - 1) {
            nums.push_back(stoi(s.substr(head, i - head + 1)));
        }
    }
    for (auto val: nums) {
        cout<< val <<endl;
    }
    n = nums.size();
    int ans[2] = {n, n + 1};
    for (int i = 0; i < n; ++i) {
        // last = i, next = i
        // 检查 pos = nums[i] - 1;
        //   if pos == i: continue;
        //   if rest.has(pos) :
        //      rest[pos_j] = last;
        //      continue;
        //   else:
        //       继续
        mySort(nums, i, i, ans);
    }
    ans[0]++;
    ans[1]++;
    cout<< "答案: "<< ans[0] << "," << ans[1] <<endl;
    return 0;
}
