// 面试题 10.10. 数字流的秩
//
// 假设你正在读取一串整数。每隔一段时间，你希望能找出数字 x 的秩(小于或等于 x 的值的个数)。请实现数据结构和算法来支持这些操作，也就是说：
//
// 实现 track(int x) 方法，每读入一个数字都会调用该方法；
//
// 实现 getRankOfNumber(int x) 方法，返回小于或等于 x 的值的个数。
//
// 注意：本题相对原题稍作改动
//
// 示例:
//
// 输入:
// ["StreamRank", "getRankOfNumber", "track", "getRankOfNumber"]
// [[], [1], [0], [0]]
// 输出:
// [null,0,null,1]
// 提示：
//
// x <= 50000
// track 和 getRankOfNumber 方法的调用次数均不超过 2000 次

#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <cmath>

using namespace std;

class CSkipTable {
    private:
        static const int MAX_LV = 16;
        bool is_head = false; // 是否是跳表头，头节点不存放数据
        int val;
        int lv;
        int span[MAX_LV]{0};         // 前一节点到当前节点的跨度, 当前节点的 rank = sum(f_span[lv]); f_span 表示同一级的所有前置 span
        CSkipTable *next[MAX_LV]{0}; // 指向的是后继节点

        int random_lv(int val) {
            for (int i = 0; i < MAX_LV; ++i) {
                if (((val >> i) & 1) == 0) {
                    return i;
                }
            }
            return MAX_LV - 1;
        }
    public:
        CSkipTable(int _val) : val(_val) {
            for (int i = 0; i < MAX_LV; ++i) {
                next[i] = this;
            }
            lv = random_lv(val);
        }

        ~CSkipTable() {
            if (is_head) {
                CSkipTable *cur = this->next[0];
                while (cur != this) {
                    CSkipTable *tp = cur;
                    cur = cur->next[0];
                    delete tp;
                }
            }
        }

        int insert(int val) {
            /*
             * 1. 创建一个新的节点，分配一个 lv 给它
             * 2. 将这个节点插入到 <= lv 的链表中
             * 3. 更新 span (所有 lv 对应的前置节点 和 新节点) :
             *         - <= lv: 前置节点 span = 新节点从当前等级下滑到0级累计移动的个数 + 1
             *            - 设置 i = [0, lv], 当 i == 0 时, 前置节点 span == j0, j0 == 1 不变(所有 0 级节点间距都是 1)
             *                              - 当 i == 1 时, 前置节点 span = j1 + 1, j1 为 新节点从 1 级前置节点下滑到 0 级后，往后移动的个数
             *                              - 当 i == 2 时, 前置节点 span = j2 + 1, j2 为 新节点从 2 级前置节点下滑到 1 级后，往后移动的个数 + j1
             *                              - 当 i == n 时, 前置节点 span = jn + 1, jn = x[n - 1] + sum(j1, ..., j[n-1]); x[n - 1] = 新节点在 n - 1 节点往后移动的个数
             *            - 新节点 span = 前置节点 旧span + 1 - 前置节点 新span
             *
             *         - > lv : 前置节点 span = span + 1
             *            - 用 update[MAX_LV] 记录需要更新 span 的前置节点
             * 4. 返回新节点 rank
             *         - sum([lv, 0][当前 lv 对应起始节点 到 前置节点之前的节点span])
             * */

            CSkipTable *new_one = new CSkipTable(val);
            CSkipTable *update[MAX_LV]{0};
            int move[new_one->lv + 1];

            int rank = 0;
            CSkipTable *pre = this;
            for (int i = MAX_LV - 1; i >= 0; --i) {
                int move_step = 0;
                CSkipTable *next = pre->next[i];
                while (next != this && next->val <= new_one->val) {
                    move_step += pre->span[i];
                    pre = next;
                    next = next->next[i];
                }
                rank += move_step;
                update[i] = pre;
                if (i > new_one->lv) {
                    pre->span[i]++;
                } else {
                    move[i] = move_step;
                }
            }

            int total_move = 0;
            for (int i = 0; i <= new_one->lv; ++i) {
                /* insert */
                new_one->next[i] = update[i]->next[i];
                update[i]->next[i] = new_one;

                /* update span */
                if (i - 1 >= 0) {
                    total_move += move[i - 1];
                }
                //new_one->span[i] = update[i]->span[i] + 1 - (total_move + 1);
                new_one->span[i] = update[i]->span[i] - total_move;
                update[i]->span[i] = total_move + 1;
            }

            return rank;
        }

        int search(int val) {
            int lv = random_lv(val);
            CSkipTable *pre = this;
            int rank = 0;
            for (int i = MAX_LV - 1; i >= lv; --i) {
                CSkipTable *cur = pre->next[i];
                while (cur != this && cur->val <= val) {
                    rank += pre->span[i];
                    pre = cur;
                    cur = cur->next[i];
                }
            }
            return rank;
        }

        vector<vector<string>> show() {
            /*
             * string:
             *      - 3位val(3位span)
             * */
            vector<vector<string>> vv;
            CSkipTable *cur = this;
            do {
                vector<string> v;
                for (int i = 0; i < MAX_LV; ++i) {
                    string s;
                    if (i <= cur->lv) {
                        char buf[9];
                        snprintf(buf, 9, "%3d(%3d)", cur->val, cur->span[i]);
                        s = buf;
                    } else {
                        s = "        ";
                    }
                    v.push_back(s);
                }
                vv.push_back(v);
                cur = cur->next[0];
            } while (cur != this);
            return vv;
        }

        void set_root() {
            this->is_head = true;
            this->lv = MAX_LV - 1;
        }
};

int main()
{
    CSkipTable *skt = new CSkipTable(0);
    skt->set_root();

    skt->search(1);
    /* test */
    for (int i = 0; i < 10; ++i) {
        int val = random() % 1000;
        int rank = skt->insert(val);
        int srank = skt->search(val);
        cout<<val<<": "<<rank<<", "<<srank<<endl;
        vector<vector<string>> show = skt->show();
        for (int j = 0; j < 16; ++j) {
            for (size_t i = 0; i < show.size(); ++i) {
                cout<<show[i][j]<<"  ";
            }
            cout<<endl;
        }
    }

    delete skt;
    return 0;
}
