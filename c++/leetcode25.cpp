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
    public:
        ListNode* reverseKGroup(ListNode* head, int k) {
            ListNode* last_tail = nullptr;
            ListNode* now_tail = nullptr;
            ListNode* now_head = nullptr;
            ListNode* old_head = nullptr;
            int i = 0;
            ListNode* new_list = nullptr;
            if (k <= 0) return head;
            while (head) {
                i++;
                if (i > k) {
                    i = 1;
                }
                if (i == 1) {
                    ListNode* new_tail = new ListNode(head->val); // 该段的当前起点，翻转后的末端
                    now_tail = new_tail;       // 该段的游标
                    now_head = new_tail;       // 该段的游标
                    old_head = head;            // 指向该段的原有链表的起点
                } else {
                    // 游标前进一格
                    ListNode* new_head = new ListNode(head->val);
                    new_head->next = now_head;
                    now_head = new_head;
                    if (i == k) {
                        if (last_tail) {
                            // 不是第一段，连接上一段
                            last_tail->next = now_head;
                        } else {
                            // 第一段结束
                            new_list = now_head;
                        }
                        last_tail = now_tail;
                    }
                }
                head = head->next;
            }
            if (i > 0 && i < k) {
                // 最后一段不能翻转
                if (last_tail) {
                    // 连接原有链表最后一段
                    last_tail->next = old_head;
                } else {
                    new_list = old_head;
                }
            }
            return new_list;
        }
};
