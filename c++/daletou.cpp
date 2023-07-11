
#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <time.h>

using namespace std;

vector<int> fetchNum(int *pool, int len, int need_num) {
    int idx;
    vector<int> ans;
    for (int i = 0; i < need_num; ++i) {
        idx = rand() % (len - i);
        ans.push_back(pool[idx]);
        swap(pool[idx], pool[len - 1 - i]);
    }
    return ans;
}

void doOne(int k) {
    static int a = 0;
    srand(time(NULL) + a++);
    int pre_pool[35];
    for (int i = 0; i < 35; ++i) {
        pre_pool[i] = i + 1;
    }
    int back_pool[12];
    for (int i = 0; i < 12; ++i) {
        back_pool[i] = i + 1;
    }
    for (int i = 0; i < k - 1; ++i) {
        fetchNum(pre_pool, 35, 5);
        fetchNum(back_pool, 12, 2);
    }
    vector<int> ans_pre = fetchNum(pre_pool, 35, 5);
    vector<int> ans_back = fetchNum(back_pool, 12, 2);
    sort(ans_pre.end() - 5, ans_pre.end());
    sort(ans_back.end() - 2, ans_back.end());
    for (int num: ans_pre) {
        cout<<num<<" ";
    }
    for (int num: ans_back) {
        cout<<num<<" ";
    }
    cout<<endl;
}

int main(int argc, char **argv) {
    if (argc != 3) return 0;
    int k = stoi(argv[1]);
    int times = stoi(argv[2]);
    for (int i = 0; i < times; ++i) {
        doOne(k);
    }
    return 0;
}
