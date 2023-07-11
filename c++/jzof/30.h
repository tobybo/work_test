#ifndef _30_H_
#define _30_H_

#include <stack>


class MinStack {

private:
	std::stack<int> data;
	std::stack<int> min_data;

public:
    /** initialize your data structure here. */
    MinStack() {

    }

    void push(int x) {
		this->data.push(x);
		if (this->data.size() == 1) {
            this->min_data.push(x);
		} else {
            int min_val = this->min_data.top();
		    min_val = min_val < x? min_val:x;
            this->min_data.push(min_val);
		}
    }

    void pop() {
		int top_val = this->data.top();
		this->data.pop();
        this->min_data.pop();
    }

    int top() {
        return this->data.top();
    }

    int min() {
        return this->min_data.top();
    }
};

#endif
