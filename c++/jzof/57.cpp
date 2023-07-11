// 输入一个递增排序的数组和一个数字s，在数组中查找两个数，使得它们的和正好是s。如果有多对数字的和等于s，则输出任意一对即可。
//
// 示例 1：
//
// 输入：nums = [2,7,11,15], target = 9
// 输出：[2,7] 或者 [7,2]
// 示例 2：
//
// 输入：nums = [10,26,30,31,47,60], target = 40
// 输出：[10,30] 或者 [30,10]
//
//
// 限制：
//
// 1 <= nums.length <= 10^5
// 1 <= nums[i] <= 10^6

// a[i] + a[j] == s return
// a[i] + a[j] < s; i++
// a[i] + a[j] > s; j--

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    vector<int> nums;
    string s;
    int sum;
    getline(cin, s);
    int head = 0;
    for (int i = 0; i < (int)s.size(); ++i) {
        if (s[i] == ' ') {
            nums.push_back(stoi(s.substr(head, i - head)));
            head = i + 1;
        }
    }
    cin>>sum;
    int i = 0, j = nums.size() - 1;
    int temp;
    while (i < j) {
        temp = nums[i] + nums[j];
        if (temp == sum) {
            cout<<nums[i]<<" "<<nums[j]<<endl;
            break;
        } else if (temp < sum) {
            i++;
        } else {
            j--;
        }
    }

    return 0;
}
