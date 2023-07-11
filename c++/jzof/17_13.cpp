// 面试题 17.13. 恢复空格
//
// 哦，不！你不小心把一个长篇文章中的空格、标点都删掉了，
// 并且大写也弄成了小写。
// 像句子"I reset the computer. It still didn’t boot!"
//已经变成了"iresetthecomputeritstilldidntboot"。
//在处理标点符号和大小写之前，你得先把它断成词语。
//当然了，你有一本厚厚的词典dictionary，不过，有些词没在词典里。
//假设文章用sentence表示，设计一个算法，把文章断开，要求未识别的字符最少，返回未识别的字符数。
//
// 注意：本题相对原题稍作改动，只需返回未识别的字符数
//
// 示例：
//
// 输入：
// dictionary = ["looked","just","like","her","brother"]
// sentence = "jesslookedjustliketimherbrother"
// 输出： 7
// 解释： 断句后为"jess looked just like tim her brother"，共7个未识别字符。
// 提示：
//
// 0 <= len(sentence) <= 1000
// dictionary中总字符数不超过 150000。
// 你可以认为dictionary和sentence中只包含小写字母。

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    class Dir {
        private:
            bool m_isEmpty = true;
            bool m_isLeaf = false;
            Dir* m_next[26] = {0};
        private:
            void insert(const string &s, size_t pos) {
                if (pos >= s.size()) {
                    m_isLeaf = true;
                    return;
                }
                int key = s[pos] - 'a';
                if (!m_next[key]) {
                    m_next[key] = new Dir();
                }
                m_next[key]->insert(s, pos + 1);
            }

            int isExist(const string &s, size_t head, size_t tail, size_t offset) const {
                size_t pos = head + offset;
                if (pos >= tail) {
                    return m_isLeaf? 1: 2;
                }
                int key = s[pos] - 'a';
                if (!m_next[key]) {
                    return 0;
                }
                return m_next[key]->isExist(s, head, tail, offset + 1);
            }
        public:
            void insert(const string &s) {
                if (s.size() == 0) return;
                m_isEmpty = false;
                insert(s, 0);
            }

            int isExist(const string &s, size_t head, size_t tail) const {
                if (head >= tail) return 0;
                return isExist(s, head, tail, 0);
            }

            bool empty() const {
                return m_isEmpty;
            }
            // bool isLeaf() const {
            //     return m_isLeaf;
            // }

            /*
             * 1. 循环 i = [0, len), 循环 j = [i + 1, len + 1);
             * 2. 查询 s[i~j) 是否在字典中
             *      - 不在:
             *          - break 内层循环
             *      - 在:
             *          - isLeaf:
             *              - 递归分支1, 继续查找更长的匹配串
             *              - 递归分支2, break 内层循环，i = j
             *          - isNotLeaf:
             *              - 继续查找更长的匹配串
             *
             * */
            int getRespace(const string &s, vector<vector<int>> &vis, int sum, size_t head, size_t tail) const {
                size_t old_tail = tail;
                int old_sum = sum;
                if (vis[head][tail] >= 0) return vis[head][tail] + old_sum;
                int ret;
                size_t len = s.size();
                for (size_t i = head; i < len; ++i) {
                    for (size_t j = tail; j < len + 1; ++j) {
                        ret = isExist(s, i, j);
                        if (!ret) {
                            sum++; // 加1 是因为 i 对应这个字符作为未匹配字符
                            break;
                        }
                        switch (ret) {
                            case 1:
                                // is leaf node
                                if (j < len) {
                                    vis[j][j + 1] = getRespace(s, vis, sum, j, j + 1) - sum;
                                    vis[i][j + 1] = getRespace(s, vis, sum, i, j + 1) - sum;
                                    vis[head][old_tail] = min(vis[j][j + 1], vis[i][j + 1]);
                                    return vis[head][old_tail] + sum;
                                    //return min(getRespace(s, vis, sum, j, j + 1), getRespace(s, vis, sum, i, j + 1));
                                }
                                vis[head][old_tail] = sum - old_sum;
                                return sum;
                            case 2:
                                // is not leaf node
                                if (i == len - 1) {
                                    // the last char
                                    vis[head][old_tail] = sum + 1 - old_sum;
                                    return sum + 1;
                                }
                                if (j == len) {
                                    sum++;
                                }
                                break;
                            default:
                                cout<<"err branch"<<endl;
                                break;
                        }
                    }
                    tail = i + 2;
                }
                vis[head][old_tail] = sum - old_sum;
                return sum;
            }
    };

    vector<vector<int>> *m_vis;
    int respace(vector<string>& dictionary, string sentence) {
        size_t len = sentence.size();
        if (!len) return 0;
        if (dictionary.empty()) return len;
        Dir dir;
        for (auto &s: dictionary) {
            dir.insert(s);
        }
        if (dir.empty()) return len;
        m_vis = new vector<vector<int>>(sentence.size() + 1, vector<int>(sentence.size() + 1, -1));
        return dir.getRespace(sentence, *m_vis, 0, 0, 1);
    }
};

const vector<string> explode(const string& s, const char& c)
{
    string buff{""};
    vector<string> v;

    for(auto n:s)
    {
        if(n != c && n != '"') buff+=n; else
            if(n == c && buff != "") { v.push_back(buff); buff = ""; }
    }
    if(buff != "") v.push_back(buff);

    return v;
}

int main()
{
    string s;
    getline(cin, s);
    vector<string> dic{explode(s, ',')};
    string sentence;
    getline(cin, sentence);
    Solution sol;
    int ans = sol.respace(dic, sentence);
    cout<<ans<<endl;
    return 0;
}


