// 面试题 16.03. 交点
//
// 给定两条线段（表示为起点start = {X1, Y1}和终点end = {X2, Y2}），如果它们有交点，请计算其交点，没有交点则返回空值。
//
// 要求浮点型误差不超过10^-6。若有多个交点（线段重叠）则返回 X 值最小的点，X 坐标相同则返回 Y 值最小的点。
//
// 示例 1：
//
// 输入：
// line1 = {0, 0}, {1, 0}
// line2 = {1, 1}, {0, -1}
// 输出： {0.5, 0}
// 示例 2：
//
// 输入：
// line1 = {0, 0}, {3, 3}
// line2 = {1, 1}, {2, 2}
// 输出： {1, 1}
// 示例 3：
//
// 输入：
// line1 = {0, 0}, {1, 1}
// line2 = {1, 0}, {2, 1}
// 输出： {}，两条线段没有交点
//
//
// 提示：
//
// 坐标绝对值不会超过 2^7
// 输入的坐标均是有效的二维坐标

#include <iostream>
#include <vector>
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

int main() {
    int k = 2;
    vector<vector<int>> input;
    for (int i = 0; i < k; ++i) {
        string s;
        getline(cin, s);
        input.push_back(explode(s, ','));
    }
    double k1, k2; // 斜率
    double z1, z2; // 常量
    bool in_x1 = false;
    bool in_x2 = false;
    // 第一条线段
    int x1 = input[0][0]; int y1 = input[0][1];
    int x2 = input[0][2]; int y2 = input[0][3];
    if (x2 == x1) {
        // 跟y轴平行的线段
        in_x1 = true;
    } else {
        k1 = ((double)(y2 - y1)) / (x2 - x1);
    }
    // 第二条线段
    int p1 = input[1][0]; int q1 = input[1][1];
    int p2 = input[1][2]; int q2 = input[1][3];
    if (p2 == p1) {
        // 跟y轴平行的线段
        in_x2 = true;
    } else {
        k2 = ((double)(q2 - q1)) / (p2 - p1);
    }
    bool has_inter_point = false;
    cout<<in_x1<<" "<<in_x2<<endl;
    double ans_x, ans_y;
    if (!in_x1 && !in_x2) {
        // y1 = k1 * x1 + z1
        // q = k2 * x + z2
        z1 = y1 - k1 * x1;
        z2 = q1 - k2 * p1;
        // y = k1 * x + z1
        // y = k2 * x + z2
        // 0 = (k1 - k2) * x + (z1 - z2)
        if (k1 == k2) {
            if (z1 != z2) {
                // 无交点
            } else {
                // 重合，检查线段是否有交点
                if ((x1 < min(p1, p2) && x2 < min(p1,p2)) || (x1 > max(p1,p2) && x2 > max(p1,p2))) {
                    // 无交点
                } else {
                    int min_x = min(x1, x2);
                    int min_p = min(p1, p2);
                    if (min_x >= p1 && min_x <= p2) {
                        ans_x = min_x;
                        ans_y = min_x == x1? y1:y2;
                    } else {
                        ans_x = min_p;
                        ans_y = min_p == p1? q1:q2;
                    }
                    has_inter_point = true;
                }
            }
        } else {
            // k1 ~= k2
            ans_x = (z2 - z1)/(k1 - k2);
            if ((ans_x < min(x1, x2) || ans_x > max(x1, x2)) || (ans_x < min(p1, p2) || ans_x > max(p1, p2))) {
                // 无交点
            } else {
                has_inter_point = true;
                ans_y = k1 * ans_x + z1;
            }
        }
    } else if (in_x1 && in_x2) {
        // 跟y轴平行的线段
        // x 是固定的常量
        if (x1 != p1) {
            // 无交点
        } else {
            if ((y1 < min(q1,q2) && y2 < min(q1,q2)) || (y1 > max(q1,q2) && y2 > max(q1,q2))) {
                // 无交点
            } else {
                // 重合
                int min_y = min(y1, y2);
                int min_q = min(q1, q2);
                if (min_y >= min(q1, q2) && min_y <= max(q1,q2)) {
                    ans_y = min_y;
                } else {
                    ans_y = min_q;
                }
                ans_x = x1;
                has_inter_point = true;
            }
        }
    } else if (in_x1) {
        // lin1 是跟y轴平行的线段
        // y = y1; x = x
        // q = k2 * p + z2;
        // ans_x = (q - z2) / k2; q = y1;
        z2 = q1 - k2 * p1;
        ans_x = x1;
        ans_y = k2 * ans_x + z2;
        if ((ans_y < min(y1, y2) || ans_y > max(y1, y2)) || (ans_y < min(q1, q2) || ans_y > max(q1, q2))) {
            // 无交点
        } else {
            has_inter_point = true;
        }
    } else if (in_x2) {
        // lin2 是跟y轴平行的线段
        z1 = y1 - k1 * x1;
        ans_x = p1;
        ans_y = k1 * ans_x + z1;
        if ((ans_y < min(y1, y2) || ans_y > max(y1, y2)) || (ans_y < min(q1, q2) || ans_y > max(q1, q2))) {
            // 无交点
        } else {
            has_inter_point = true;
        }
    }
    if (!has_inter_point) {
        cout<<"{"<<" }"<<endl;
    } else {
        cout<<"{ ";
        cout<<ans_x<<","<<ans_y;
        cout<<" }"<<endl;
    }
    return 0;
}

