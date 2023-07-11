// 面试题 16.02. 单词频率
//
// 设计一个方法，找出任意指定单词在一本书中的出现频率。
//
// 你的实现应该支持如下操作：
//
// WordsFrequency(book)构造函数，参数为字符串数组构成的一本书
// get(word)查询指定单词在书中出现的频率
// 示例：
//
// WordsFrequency wordsFrequency = new WordsFrequency({"i", "have", "an", "apple", "he", "have", "a", "pen"});
// wordsFrequency.get("you"); //返回0，"you"没有出现过
// wordsFrequency.get("have"); //返回2，"have"出现2次
// wordsFrequency.get("an"); //返回1
// wordsFrequency.get("apple"); //返回1
// wordsFrequency.get("pen"); //返回1
// 提示：
//
// book[i]中只包含小写字母
// 1 <= book.length <= 100000
// 1 <= book[i].length <= 10
// get函数的调用次数不会超过100000

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class worldDir {
  public:
    /* data */
    worldDir* next[26] = {0};
    int times = 0;
  public:
    void insert(string &s) {
        int n = s.size();
        if (!n) return;
        fill(s, 0);
    }

    void fill(string &s, unsigned int pos) {
        int c = s[pos] - 'a';
        if (!next[c]) {
            next[c] = new worldDir();
        }
        if (pos + 1 < s.size()) {
            next[c]->fill(s, pos + 1);
        } else {
            next[c]->times++;
        }
    }

    int count(string &s, unsigned int pos) {
        if (!s.size()) return 0;
        int c = s[pos] - 'a';
        if (!next[c]) {
            return 0;
        } else {
            if (pos + 1 < s.size()) {
                return next[c]->count(s, pos + 1);
            } else {
                return next[c]->times;
            }
        }
    }

};

class WordsFrequency {
  private:
    worldDir dir;
  public:
    WordsFrequency(vector<string> &v) {
        for (string &s: v) {
            dir.insert(s);
        }
    }
    virtual ~WordsFrequency() {}

  public:
    int get(string &s) {
        return dir.count(s, 0);
    }
};

const vector<string> explode(const string& s, const char& c)
{
    string buff{""};
    vector<string> v;

    for(auto n:s)
    {
        if(n >= 'a' && n <= 'z') buff+=n; else
            if(n == c && buff != "") { v.push_back(buff); buff = ""; }
    }
    if(buff != "") v.push_back(buff);

    return v;
}

int main() {
    int k;
    cin>>k;
    cin.ignore();
    string s;
    getline(cin, s);
    vector<string> input{explode(s, ',')};

    for (string &s: input) {
        cout<<"input: "<<s<<endl;
    }
    WordsFrequency w(input);

    getline(cin, s);
    do {
        cout<<s<<": "<<w.get(s)<<endl;
        getline(cin, s);
    } while(!s.empty());

    return 0;
}




