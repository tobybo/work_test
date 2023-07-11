

// 定义一个函数，输入一个链表的头节点，反转该链表并输出反转后链表的头节点。
//
// 示例:
// 输入: 1->2->3->4->5->NULL
// 输出: 5->4->3->2->1->NULL
//
// 限制：
// 0 <= 节点个数 <= 5000

#ifndef _24_h_
#define _24_h_

#include <iostream>
#include <stack>
using namespace std;

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
	struct ListNode {
		int val;
		ListNode *next;
		ListNode(int x) : val(x), next(NULL) {}
	};
    ListNode* reverseList(ListNode *head) {
        if (!head) return NULL;
        ListNode *pre = NULL;
        ListNode *cur = head;
        ListNode *temp = NULL;
        while (cur) {
            temp = cur->next;
            cur->next = pre;
            pre = cur;
            cur = temp;
        }
        return pre;
    }
};

#endif
