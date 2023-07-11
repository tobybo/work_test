// 输入一个链表的头节点，从尾到头反过来返回每个节点的值（用数组返回）。
//
//
//
// 示例 1：
//
// 输入：head = [1,3,2]
// 输出：[2,3,1]
//
//
// 限制：
//
// 0 <= 链表长度 <= 10000

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

#ifndef _06_h_
#define _06_h_

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class Solution {
public:
	struct ListNode {
		int val;
		ListNode *next;
		ListNode(int x) : val(x), next(NULL) {}
	};
public:
    vector<int> reversePrint(ListNode* head) {
        vector<int> ans(0);
		stack<int> temp_stack;
        while (head) {
		    temp_stack.push(head->val);
            head = head->next;
        }
        int size = temp_stack.size();
        for (int i = 0; i < size; ++i) {
            ans.push_back(temp_stack.top());
            temp_stack.pop();
        }
        return ans;
    }
};

#endif
