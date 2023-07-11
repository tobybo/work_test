

class Solution {
public:
    double myPow(double x, int n) {
        if (n == 0) return 1;
        int abs_n = abs(n);
        double ans = x;
        stack<double> stk;
        int cur_n = abs_n;
        while (cur_n / 2 >= 1) {
            if (cur_n & 1) {
                stk.push(x);
            } else {
                stk.push(1);
            }
            cur_n = cur_n / 2;
        }
        while (stk.size() > 0) {
            ans *= ans * stk.top();
            stk.pop();
        }
        if (n > 0) {
            return ans;
        } else {
            return 1/ans;
        }
    }
};
