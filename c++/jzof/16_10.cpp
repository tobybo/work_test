// 面试题 16.10. 生存人数
//
// 给定 N 个人的出生年份和死亡年份，第 i 个人的出生年份为 birth[i]，死亡年份为 death[i]，实现一个方法以计算生存人数最多的年份。
//
// 你可以假设所有人都出生于 1900 年至 2000 年（含 1900 和 2000 ）之间。如果一个人在某一年的任意时期处于生存状态，那么他应该被纳入那一年的统计中。例如，生于 1908 年、死于 1909 年的人应当被列入 1908 年和 1909 年的计数。
//
// 如果有多个年份生存人数相同且均为最大值，输出其中最小的年份。
//
//
//
// 示例：
//
// 输入：
// birth = [1900, 1901, 1950]
// death = [1948, 1951, 2000]
// 输出： 1901
//
//
// 提示：
//
// 0 < birth.length == death.length <= 10000
// birth[i] <= death[i]

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

const vector<string> explodes(const string& s, const char& c)
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

int main(void)
{
    string s1, s2;
    getline(cin, s1);
    getline(cin, s2);
    vector<int> birth{explode(s1, ',')};
    vector<int> death{explode(s2, ',')};

    sort(birth.begin(), birth.end());
    sort(death.begin(), death.end());
    int sum, last_year;
    int max_sum, max_year;
    sum = max_sum = max_year = 0;
    size_t i, j;
    for (i = 0, j = 0; i < birth.size(); ++i) {
        if (birth[i] <= death[j]) {
            sum++;
            last_year = birth[i];
        } else {
            if (sum > max_sum) {
                max_sum = sum;
                max_year = last_year;
            }
            while (birth[i] > death[j]) {
                j++;
                sum--;
            }
            i--;
        }
    }
    if (sum > max_sum) {
        max_sum = sum;
        max_year = last_year;
    }
    cout<<max_year<<endl;

    return 0;
}
