
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class my_compare {
    public:
        bool operator()(vector<int> &a, vector<int> &b) {
            return a[0] < b[0];
        }
};

int main() {
    vector<int> input {3,2,1,3,5};
    auto compare = [](vector<int> &a, vector<int> &b){
        return a[0] < b[0];
    };
    priority_queue<vector<int>, vector<vector<int>>, my_compare> q;
    for (int i = 0; i < input.size(); ++i) {
        //q.emplace(vector<int>({input[i], i}));
        q.emplace(vector<int>{input[i], i});
        cout<<"max: "<< q.top()[0] << ", idx: " << q.top()[1] <<endl;
    }
    return 0;
}

