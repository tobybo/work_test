// 面试题 16.20. T9键盘
//
// 在老式手机上，用户通过数字键盘输入，
// 手机将提供与这些数字相匹配的单词列表。
// 每个数字映射到0至4个字母。给定一个数字序列，
// 实现一个算法来返回匹配单词的列表。你会得到一张含有有效单词的列表。映射如下图所示：
//
//
//
// 示例 1:
//
// 输入: num = "8733", words = ["tree", "used"]
// 输出: ["tree", "used"]
// 示例 2:
//
// 输入: num = "2", words = ["a", "b", "c", "d"]
// 输出: ["a", "b", "c"]
// 提示：
//
// num.length <= 1000
// words.length <= 500
// words[i].length == num.length
// num中不会出现 0, 1 这两个数字


#include <iostream>
#include <vector>
#include <string>

using namespace std;

const vector<string> explode(const string& s, const char& c)
{
    string buff{""};
    vector<string> v;

    for(auto n:s)
    {
        if(n != c && n != ' ' && n != '"') buff+=n; else
            if(n == c && buff != "") { v.push_back(buff); buff = ""; }
    }
    if(buff != "") v.push_back(buff);

    return v;
}

class wordDir {
    public:
       wordDir *next = nullptr;
       bool data[26] = {0};

       wordDir(const string &s) {
           for (auto c: s) {
               data[c - 'a'] = true;
           }
       }

       wordDir *append(const string &s) {
           wordDir *tail = this;
           while (tail->next) {
               tail = tail->next;
           }
           tail->next = new wordDir(s);
           return tail;
       }

       bool find(const string &s, size_t pos) {
           if (pos >= s.size()) return false;
           if (!data[s[pos] - 'a']) return false;
           if (pos == s.size() - 1) return true;
           return next && next->find(s, pos + 1);
       }
};

int main()
{
    string num;
    cin>>num;
    cin.ignore();
    string s;
    getline(cin, s);
    vector<string> input{explode(s, ',')};

    const string MAP[8]{
        "abc",
        "def",
        "ghi",
        "jkl",
        "mno",
        "pqrs",
        "tuv",
        "wxyz",
    };
    wordDir *dir = nullptr;
    for (size_t i = 0; i < num.size(); ++i) {
        if (i) {
            dir->append(MAP[num[i] - '2']);
        } else {
            dir = new wordDir(MAP[num[i] - '2']);
        }
    }
    vector<string> ans;
    for (auto &s: input) {
        if (dir->find(s, 0)) {
            ans.push_back(s);
            cout<<s<<" ";
        }
    }
    cout<<endl;

    return 0;
}


