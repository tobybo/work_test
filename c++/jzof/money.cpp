
#include <iostream>
#include <unordered_map>

using namespace std;

class Sol {
    private:
        const int ARR[4] = {25, 10, 5, 1};
        const int MAX_N = 1000000007;
        unordered_map<int, int> cache;
        // 49: 25 + 24, 39 种
        // 25: 13 种
        // 24: 9 种
        // 14: 4 种
        // 10: 4 种
        // 4:  1 种
    public:
        int calculate(int k) {
            int sum = 0;
            int rest_val = k;
            int sub_rest_val = 0;
            int n = rest_val / 25;
            for (int i25 = n; i25 >= 0; --i25) {
                rest_val = k - i25 * 25;
                int m = rest_val / 10;
                for (int i10 = m; i10 >= 0; --i10) {
                    sub_rest_val = rest_val - i10 * 10;
                    if (cache.find(sub_rest_val) != cache.end()) {
                        sum = (sum + cache[sub_rest_val]) % MAX_N;
                    } else {
                        int j = sub_rest_val / 5;
                        int temp = (j + 1) % MAX_N;
                        cache[sub_rest_val] = temp;
                        sum = (sum + temp) % MAX_N;
                    }
                }
            }
            return sum;
        }
};

int main() {
    int k;
    cin>>k;
    Sol sol;
    cout<<sol.calculate(k)<<endl;
    return 0;
}
