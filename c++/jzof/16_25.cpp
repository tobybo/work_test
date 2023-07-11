// 面试题 16.25. LRU 缓存
//
// 设计和构建一个“最近最少使用”缓存，该缓存会删除最近最少使用的项目。
// 缓存应该从键映射到值(允许你插入和检索特定键对应的值)，并在初始化时指定最大容量。
// 当缓存被填满时，它应该删除最近最少使用的项目。
//
// 它应该支持以下操作： 获取数据 get 和 写入数据 put 。
//
// 获取数据 get(key) - 如果密钥 (key) 存在于缓存中，则获取密钥的值（总是正数），否则返回 -1。
// 写入数据 put(key, value) - 如果密钥不存在，则写入其数据值。
// 当缓存容量达到上限时，它应该在写入新数据之前删除最近最少使用的数据值，从而为新的数据值留出空间。
//
// 示例:
//
// LRUCache cache = new LRUCache( 2 [> 缓存容量 <] );
//
// cache.put(1, 1);
// cache.put(2, 2);
// cache.get(1);       // 返回  1
// cache.put(3, 3);    // 该操作会使得密钥 2 作废
// cache.get(2);       // 返回 -1 (未找到)
// cache.put(4, 4);    // 该操作会使得密钥 1 作废
// cache.get(1);       // 返回 -1 (未找到)
// cache.get(3);       // 返回  3
// cache.get(4);       // 返回  4

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;
class LRUCache {
    private:
        class ListNode {
            public:
                int key = -10;
                int val = -10;
                ListNode *next = nullptr;
                ListNode *pre = nullptr;
                ListNode() : next(this), pre(this) {}
                void outlist() {
                    if (next) {
                        pre->next = next;
                        next->pre = pre;
                        next = this;
                        pre = this;
                    }
                }
                void insert(ListNode *_next) {
                    this->next = _next;
                    this->pre = _next->pre;
                    _next->pre = this;
                    this->pre->next = this;
                }
        };

        ListNode head;
        int cur_cap = 0;
        int max_cap;
        unordered_map<int, ListNode*> hash;
    public:
        LRUCache(int capacity) : max_cap(capacity) {

        }

        /*
         * 用一个hash表存储 [key, list_node]
         * 将该node放到list的末尾
         * get 的node 要检查是否在list中
         * 不在的话需要释放内存返回-1
         * */
        int get(int key) {
            int ans = -1;
            auto itor = hash.find(key);
            if (itor != hash.end()) {
                if (itor->second->val == -1) {
                    delete itor->second;
                    hash.erase(itor);
                } else {
                    ans = itor->second->val;
                    itor->second->outlist();
                    itor->second->insert(&head); // 插入到最后
                }
            }
            return ans;
        }

        /*
         * 先检查是否存在,
         * 存在取到 node, 替换值
         * 不存在
         * 用一个链表记录节点插入顺序
         * 如果容量超出, 将 list 头部节点从list中删除，
         * 但是节点数据保留, get 的时候进行释放
         * node = new node
         *
         * 插入到list 末尾
         * */

        bool check_cap() {
            cout<<"curcap, "<<cur_cap<<", max, "<<max_cap<<endl;
            if (this->cur_cap >= this->max_cap) {
                if (this->head.next != &(this->head)) {
                    //cout<<"rem, val: "<<head.next->val<<", next: "<<head.next->next->val<<endl;
                    this->head.next->val = -1;
                    this->head.next->outlist();
                    this->cur_cap--;
                }
            }
            if (this->cur_cap >= this->max_cap) {
                return false;
            }
            return true;
        };

        void put(int key, int value) {
            auto itor = hash.find(key);
            if (itor != hash.end()) {
                if (itor->second->val == -1) {
                    if (!check_cap()) return;
                    cur_cap++;
                }
                cout<<"old, key: "<<key<<", value: "<<itor->second->val<<"-->"<<value<<endl;
                itor->second->val = value;
                itor->second->outlist();
                itor->second->insert(&head); // 插入到最后
            } else {
                if (!check_cap()) return;
                ListNode *node = new ListNode;
                node->key = key;
                node->val = value;
                node->insert(&head); // 插入到最后
                hash[key] = node;
                cur_cap++;
            }
        }

        void show() {
            ListNode *cur = head.next;
            while (cur != &head) {
                cout<<"("<<cur->key<<","<<cur->val<<"), ";
                cur = cur->next;
            }
            cout<<endl;
        }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

const vector<string> explodes(const string& s, const char& c)
{
    string buff{""};
    vector<string> v;

    for(auto n:s)
    {
        if(n != c && n != '[' && n != ']' && n != '"') buff+=n; else
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
        if(n != c && n != '[' && n != ']' && n != '"') buff+=n; else
            if(n == c && buff != "") { v.push_back(stoi(buff)); buff = ""; }
    }
    if(buff != "") v.push_back(stoi(buff));

    return v;
}

int main()
{
    // LRUCache lru(2);
    // lru.put(2, 2);
    // lru.put(1, 5);
    // lru.put(2, 3);
    // cout<<"2: "<<lru.get(2)<<endl;
    // lru.put(3, 6);
    // cout<<"1: "<<lru.get(1)<<endl;
    // cout<<"2: "<<lru.get(2)<<endl;
    // cout<<"3: "<<lru.get(3)<<endl;

    // for input
    int cap;
    cin>>cap; cin.ignore();
    vector<string> opt;
    vector<vector<int>> args;
    string s;
    getline(cin, s);
    opt = explodes(s, ',');
    getline(cin, s, ']');
    while (s.size()) {
        vector<int> temp{explode(s, ',')};
        args.push_back(temp);
        getline(cin, s, ']');
    }
    LRUCache lru(cap);
    for (size_t i = 1; i < opt.size(); ++i) {
        if (opt[i] == "put") {
            lru.put(args[i][0], args[i][1]);
            printf("put: [%d] = [%d]\n", args[i][0], args[i][1]);
        } else if (opt[i] == "get") {
            printf("get: [%d] = [%d]\n", args[i][0], lru.get(args[i][0]));
        }
        lru.show();
    }

    return 0;
}
