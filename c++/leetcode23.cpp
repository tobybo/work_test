/**
 *  * Definition for singly-linked list.
 *  * struct ListNode {
 *  *     int val;
 *  *     ListNode *next;
 *  *     ListNode() : val(0), next(nullptr) {}
 *  *     ListNode(int x) : val(x), next(nullptr) {}
 *  *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 *  * };
 *  */
class Solution {

    private:
        // 插入一个元素到指定元素后面合适位置
        void insertOne(ListNode* head, ListNode* one) {
            while(true) {
                if (!head->next) {
                    head->next = one;
                    break;
                }
                if (head->next->val >= one->val) {
                    one->next = head->next;
                    head->next = one;
                    break;
                }
                head = head->next;
            }
        }

    public:
        ListNode* mergeKLists(vector<ListNode*>& lists) {
            if (lists->size() <= 0) return nullptr;
            ListNode* new_list = nullptr;
            ListNode* temp_next = nullptr;
            vector<ListNode*> heads(lists->size(), nullptr);
            int do_loop = 1;
            while (do_loop) {
                do_loop = 0;
                for (int i = 0; i < lists.size(); ++i) {
                    if (lists[i]) {
                        do_loop = 1;
                        temp_next = lists[i]->next;
                        if (!new_list) {
                            new_list = lists[i];
                        } else {
                            if (heads[i]) {
                                insertOne(heads[i], lists[i]);
                            } else {
                                insertOne(new_list, lists[i]);
                            }
                        }
                        heads[i] = lists[i];
                        lists[i] = temp_next;
                    }
                }
            }
            return new_list;
        }
};
