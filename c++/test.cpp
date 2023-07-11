#include <iostream>
#include <map>
#include <vector>

using namespace std;

class Solution {
    public:
        struct Node {
            int head;
            int tail;
            int num;
            Node(int a):head(a), tail(a), num(1) {

            }
            Node(Node &&a):head(a.head), tail(a.tail), num(a.num) {}
        };

        int findShortestSubArray(vector<int>& nums) {
            vector<Node> vec;
            map<int, int> valMap; //<val, vecId>
            map<int, int>::iterator itr;
            for (int id = 0; id < nums.size(); ++id) {
                cout<<"id: "<<id<<" begin"<<endl;
                itr = valMap.find(nums[id]);
                if (itr == valMap.end()) {
                    Node node(id);
                    cout<<"1111"<<endl;
                    vec.push_back(std::move(node));
                    cout<<"2222"<<endl;
                    valMap[nums[id]] = vec.size() - 1;
                } else {
                    cout<<"3333"<<endl;
                    vec[itr->second].tail = id;
                    vec[itr->second].num++;
                    cout<<"4444"<<endl;
                }
                cout<<"id: "<<id<<" end"<<endl;
            }
            return 0;
        }

};

int main() {
    vector<int> nums = {1,2,2,3,1,4,2};
    Solution sol;
    int ret = sol.findShortestSubArray(nums);
    cout<<ret<<endl;
    return 0;
}

