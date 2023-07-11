class MinStack {
public:
    /** initialize your data structure here. */
    long long num_min;
    stack<long long> stack_diff;
    MinStack() {
    }

    void push(int x) {
        if(stack_diff.empty())
        {
            num_min = x;
            stack_diff.push(0);
            return;
        }
        stack_diff.push((long long)x-num_min);
        if(x < num_min)
        {
            num_min = x;
        }
    }

    void pop() {
        if(stack_diff.top() < 0)
        {
            num_min -= stack_diff.top();
        }
        stack_diff.pop();
    }

    int top() {
        if(stack_diff.top() >= 0)
        {
            return stack_diff.top()+num_min;
        }
        else
        {
            return num_min;
        }
    }

    int min() {
        return num_min;
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(x);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->min();
 */
