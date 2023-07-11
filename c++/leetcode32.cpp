class Solution {
    private:
        stack<int> left_stack;
        int getLength(const string &s, int idx) {
            int ret = 0;
            int left_idx = idx;
            int temp_idx = -1;
            for (int i = idx; i < s.size(); i++) {
                if (s[i] == '(') {
                    this->left_stack.push(i);
                } else {
                    if (this->left_stack.size() > 0) {
                        if (temp_idx == -1) {
                            temp_idx = this->left_stack.top();
                        } else {
                            temp_idx = min(temp_idx, this->left_stack.top());
                        }
                        this->left_stack.pop();
                    } else {
                        ret = i - left_idx;
                        break;
                    }
                }
            }
            if (this->left_stack.size() > 0 && temp_idx >= 0) {
                ret = s.size() - temp_idx - 1;
            }
            return ret;
        }
    public:
        int longestValidParentheses(string s) {
            int ret = 0;
            int temp = 0;
            for (int i = 0; i < s.size(); i++) {
                temp = getLength(s, idx);
                ret = max(ret, temp);
                if (temp > 0) {
                    i += temp;
                }
            }
            return ret;
        }
};
