
// 请实现 copyRandomList 函数，复制一个复杂链表。在复杂链表中，每个节点除了有一个 next 指针指向下一个节点，还有一个 random 指针指向链表中的任意节点或者 null。
//
// 示例 1：
// 输入：head = [[7,null],[13,0],[11,4],[10,2],[1,0]]
// 输出：[[7,null],[13,0],[11,4],[10,2],[1,0]]
//
// 示例 2：
// 输入：head = [[1,1],[2,1]]
// 输出：[[1,1],[2,1]]
//
// 示例 3：
// 输入：head = [[3,null],[3,0],[3,null]]
// 输出：[[3,null],[3,0],[3,null]]
// 示例 4：
//
// 输入：head = []
// 输出：[]
// 解释：给定的链表为空（空指针），因此返回 null。
//
// 提示：
// -10000 <= Node.val <= 10000
// Node.random 为空（null）或指向链表中的节点。
// 节点数目不超过 1000 。


/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

#ifndef _35_h_
#define _35_h_

#include <iostream>
#include <map>
#include <vector>
using namespace std;

class Solution {
public:
	class Node {
		public:
			int val;
			Node* next;
			Node* random;

			Node(int _val) {
				val = _val;
				next = NULL;
				random = NULL;
			}
	};

    /*
     * 1. 给原链表每个指针编号
     * 2. 复制一个新链表，包括random指针，并且把新链表的指针存到一个数组中
     * 3. 遍历新链表，读取random指针，查到原链表中的编号，然后通过编号查到数组中的新指针
     * 4. 赋值random指针
     *
     * */
    Node* copyRandomList(Node* head) {
        if (!head) return NULL;
        map<Node *, Node *> pointer_addr;
        Node *tail = head;
        Node *new_head = NULL;
        Node *copy_head = NULL;
        while (tail) {
            Node *node = new Node(tail->val);
            node->random = tail->random;
            node->next = tail;

            std::pair<Node *, Node *> val = make_pair(tail, node);
            pointer_addr.insert(val);

            tail = tail->next;

            if (!new_head) {
                new_head = node;
                copy_head = node;
            } else {
                copy_head->next = node;
                copy_head = node;
            }
        }
        tail = new_head;
        while (tail) {
            if (tail->random) {
                auto itor = pointer_addr.find(tail->random);
                tail->random = itor->second;
            }
            tail = tail->next;
        }
        return new_head;
    }
};

#endif
