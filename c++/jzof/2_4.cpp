// 面试题 02.04. 分割链表
//
// 给你一个链表的头节点 head 和一个特定值 x ，请你对链表进行分隔，使得所有 小于 x 的节点都出现在 大于或等于 x 的节点之前。
//
// 你不需要 保留 每个分区中各节点的初始相对位置。
//
// 示例 1：
//
// 输入：head = [1,4,3,2,5,2], x = 3
// 输出：[1,2,2,4,3,5]
// 示例 2：
//
// 输入：head = [2,1], x = 2
// 输出：[1,2]
//
//
// 提示：
//
// 链表中节点的数目在范围 [0, 200] 内
// -100 <= Node.val <= 100
// -200 <= x <= 200


#include <iostream>
#include <vector>
#include <string>

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

class ListNode {
    public:
        int val = 0;
        ListNode *next = nullptr;
    public:
        ListNode(int _val) : val(_val) {
        }

        void insert(int val) {
            this->next = new ListNode(val);
        }

};

ListNode *partition(ListNode *head, int x) {
    ListNode *cur = head;
    head = nullptr;
    ListNode *last_less = nullptr;
    ListNode *bigger = nullptr;
    ListNode *last_bigger = nullptr;
    while (cur) {
        if (cur->val < x) {
            if (!last_less) {
                head = cur;
            } else {
                last_less->next = cur;
            }
            last_less = cur;
        } else {
            if (!bigger) {
                bigger = cur;
            } else {
                last_bigger->next = cur;
            }
            last_bigger = cur;
        }
        cur = cur->next;
    }
    if (last_bigger) {
        last_bigger->next = nullptr;
    }
    if (last_less) {
        last_less->next = bigger;
    } else {
        head = bigger;
    }
    return head;
}


int main(void)
{
    string s;
    getline(cin, s);

    vector<int> input{explode(s, ',')};
    if (input.size()) {
        ListNode *head = new ListNode(input[0]);
        ListNode *cur = head;
        for (size_t i = 1; i < input.size(); ++i) {
            cur->insert(input[i]);
            cur = cur->next;
        }
        int x;
        while (true) {
            cout<<"input your specify num: ";
            cin>>x;
            head = partition(head, x);
            ListNode *cur = head;
            while (cur) {
                cout<<cur->val<<" ";
                cur = cur->next;
            }
            cout<<endl;
        }

    }

    return 0;
}

