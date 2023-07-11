// 随机产生数字并传递给一个方法。你能否完成这个方法，在每次产生新值时，寻找当前所有值的中间值（中位数）并保存。
//
// 中位数是有序列表中间的数。如果列表长度是偶数，中位数则是中间两个数的平均值。
//
// 例如，
//
// [2,3,4] 的中位数是 3
//
// [2,3] 的中位数是 (2 + 3) / 2 = 2.5
//
// 设计一个支持以下两种操作的数据结构：
//
// void addNum(int num) - 从数据流中添加一个整数到数据结构中。
// double findMedian() - 返回目前所有元素的中位数。
// 示例：
//
// addNum(1)
// addNum(2)
// findMedian() -> 1.5
// addNum(3)
// findMedian() -> 2

#include <iostream>
#include <queue>
#include <string>

using namespace std;

const vector<int> explode(const string& s, const char& c)
{
    string buff{""};
    vector<int> v;

    for(auto n:s)
    {
        if(n != c) buff+=n; else
            if(n == c && buff != "") { v.push_back(stoi(buff)); buff = ""; }
    }
    if(buff != "") v.push_back(stoi(buff));

    return v;
}

class CMyClass {
        priority_queue<int, vector<int>, std::less<int>> left_q;
        priority_queue<int, vector<int>, std::greater<int>> right_q;
        double median = 0;
        int size = 0;
    public:
        void addNum(int num) {
            if (!size) {
                median = num;
                size++;
                return;
            }
            if (size & 1) {
                // 左右均衡
                if (num > median) {
                    left_q.push(median);
                    right_q.push(num);
                } else {
                    left_q.push(num);
                    right_q.push(median);
                }
                median = (left_q.top() + right_q.top()) / 2.0;
            } else {
                // 插入之后会多出一个
                if (num > median) {
                    right_q.push(num);
                    median = right_q.top();
                    right_q.pop();
                } else {
                    left_q.push(num);
                    median = left_q.top();
                    left_q.pop();
                }
            }
            size++;
        }

        double findMedian() {
            return median;
        }
};

int main() {
    string s;
    getline(cin, s);
    vector<int> input = explode(s, ',');
    CMyClass sol;
    for (int num: input) {
        sol.addNum(num);
        cout<<sol.findMedian()<<" ";
    }
    cout<<endl;
    return 0;
}
