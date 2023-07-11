// 输入两个递增排序的链表，合并这两个链表并使新链表中的节点仍然是递增排序的。
//
// 示例1：
//
// 输入：1->2->4, 1->3->4
// 输出：1->1->2->3->4->4
// 限制：
//
// 0 <= 链表长度 <= 1000

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode *l = l1, *r = l2;
        ListNode *m = NULL, *ans = NULL;
        while (l && r) {
            if (l->val <= r->val) {
                if (!m) {
                    m = l;
                    ans = m;
                } else {
                    m->next = l;
                    m = m->next;
                }
                l = l->next;
            } else {
                if (!m) {
                    m = r;
                    ans = m;
                } else {
                    m->next = r;
                    m = m->next;
                }
                r = r->next;
            }
        }
        while (l) {
            if (!m) {
                m = l;
                ans = m;
            } else {
                m->next = l;
                m = m->next;
            }
            l = l->next;
        }
        while (r) {
            if (!m) {
                m = r;
                ans = m;
            } else {
                m->next = r;
                m = m->next;
            }
            r = r->next;
        }
        return m;
    }
};
