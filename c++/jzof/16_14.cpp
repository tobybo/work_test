// 面试题 16.14. 最佳直线
//
// 给定一个二维平面及平面上的 N 个点列表Points，其中第i个点的坐标为Points[i]=[Xi,Yi]。请找出一条直线，其通过的点的数目最多。
//
// 设穿过最多点的直线所穿过的全部点编号从小到大排序的列表为S，你仅需返回[S[0],S[1]]作为答案，若有多条直线穿过了相同数量的点，则选择S[0]值较小的直线返回，S[0]相同则选择S[1]值较小的直线返回。
//
// 示例：
//
// 输入： [[0,0],[1,1],[1,0],[2,0]]
// 输出： [0,2]
// 解释： 所求直线穿过的3个点的编号为[0,2,3]
// 提示：
//
// 2 <= len(Points) <= 300
// len(Points[i]) = 2

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class Solution {
    private:
        class Coor {
            public:
                int x,y;
                virtual Coor& operator--() = 0;
                virtual Coor& operator++() = 0;
                virtual Coor* clone() = 0;
                virtual ~Coor(){}
        };
        class CoorHorizontal   : public Coor {
            virtual Coor& operator--() override {
                this->x--;
                return *this;
            }
            virtual Coor& operator++() override {
                this->x++;
                return *this;
            }
            virtual Coor* clone() override {
                return new CoorHorizontal;
            }
        };
        class CoorVirtical     : public Coor {
            virtual Coor& operator--() override {
                this->y--;
                return *this;
            }
            virtual Coor& operator++() override {
                this->y++;
                return *this;
            }
            virtual Coor* clone() override {
                return new CoorVirtical;
            }
        };
        class CoorForwardSlash : public Coor {
            virtual Coor& operator--() override {
                this->x++;
                this->y--;
                return *this;
            }
            virtual Coor& operator++() override {
                this->x--;
                this->y++;
                return *this;
            }
            virtual Coor* clone() override {
                return new CoorForwardSlash;
            }
        };
        class CoorBackSlash    : public Coor {
            virtual Coor& operator--() override {
                this->x--;
                this->y--;
                return *this;
            }
            virtual Coor& operator++() override {
                this->x++;
                this->y++;
                return *this;
            }
            virtual Coor* clone() override {
                return new CoorBackSlash;
            }
        };
public:
    typedef unordered_map<int, unordered_map<int, int>> mymap;
    vector<int> bestLine(vector<vector<int>>& points) {
        // 0. ans_len 初始为 2, ans_min = 0, ans_second = 1
        int ans_len = 2;
        int ans_min = 0;
        int ans_second = 1;
        // 1. 循环 i = [0, len)
        //         - 生成 map1 = hash<x, hash<y, id>>
        //         - map2 = map3 = map4 = map1; 得到三分map分别用于——|\/ 的计算
        mymap map1, map2, map3, map4;
        //map<int, map<int, int>> map1, map2, map3, map4;
        int len = points.size();
        for (int i = 0; i < len; ++i) {
            map1[points[i][0]][points[i][1]] = i;
        }
        map2 = map3 = map4 = map1;
        // 2. 循环 i = [0, len)
        //         - 分别在四个map中查找 points[i]
        //              找不到 continue
        //              找到了 进行下一步
        //         - 每个map 有一个 left(x1, y1)和right(x2, y2) ，初始=points[i], min_id = second_id = i, cur_len = 当前直线长度
        //         - 从map中移除 points[i]
        //         - 循环 (left-1 存在)
        //                 - left--, cur_len++, second_id = min(newid, second_id), if second_id < min_id then swap(min_id, second_id)
        //                 - if cur_len > ans_len, ans_len = cur_len, ans_min = min_id, ans_second = second_id
        //                 - if cur_len == ans_len
        //                         - if min_id < ans_min, ans_min = min_id, ans_second = second_id
        //                         - if min_id == ans_min && second_id < ans_second, ans_second = second_id
        //                 - 从map中移除 left-1
        //         - 循环 (right+1 存在)
        //                 - right++, cur_len++, second_id = min(newid, second_id), if second_id < min_id then swap(min_id, second_id)
        //                 - if cur_len > ans_len, ans_len = cur_len, ans_min = min_id, ans_second = second_id
        //                 - if cur_len == ans_len
        //                         - if min_id < ans_min, ans_min = min_id, ans_second = second_id
        //                         - if min_id == ans_min && second_id < ans_second, ans_second = second_id
        //                 - 从map中移除 right+1
        int min_id, second_id, cur_len, newid;
        CoorHorizontal cor1;
        CoorVirtical cor2;
        CoorForwardSlash cor3;
        CoorBackSlash cor4;
        for (int i = 0; i < len; ++i) {
            int cur_x = points[i][0];
            int cur_y = points[i][1];

            auto do_search = [&](mymap &map, Coor *cor){
                auto exist = [&map](int x, int y)->bool{
                    auto itor = map.find(x);
                    if (itor == map.end()) return false;
                    auto itor_inner = (itor->second).find(y);
                    if (itor_inner == itor->second.end()) return false;
                    return true;
                };
                if (!exist(cur_x, cur_y)) return;
                min_id = second_id = map[cur_y][cur_x];
                map[cur_y].erase(cur_x);
                cur_len = 1;
                cor->x = cur_x;
                cor->y = cur_y;
                Coor *right_cor = cor->clone();
                do {
                    --(*cor);
                    if (!exist(cor->x, cor->y)) break;
                    cur_len++;
                    newid = map[cor->x][cor->y];
                    printf("cor,%d,%d, newid,%d\n", cor->x, cor->y, newid);
                    map[cor->y].erase(cor->x);
                    if (second_id == min_id) {
                        second_id = newid;
                    } else {
                        second_id = min(second_id, newid);
                    }
                    if (second_id < min_id) {
                        swap(second_id, min_id);
                    }
                } while(1);

                do {
                    ++(*right_cor);
                    if (!exist(right_cor->x, right_cor->y)) break;
                    cur_len++;
                    newid = map[right_cor->x][right_cor->y];
                    printf("cor,%d,%d, newid,%d\n", right_cor->x, right_cor->y, newid);
                    map[right_cor->y].erase(right_cor->x);
                    if (second_id == min_id) {
                        second_id = newid;
                    } else {
                        second_id = min(second_id, newid);
                    }
                    if (second_id < min_id) {
                        swap(second_id, min_id);
                    }
                } while(1);

                printf("curlen,%d, ans_len,%d, min_id,%d, second,%d\n", cur_len, ans_len, min_id, second_id);
                if (cur_len > ans_len) {
                    ans_len = cur_len;
                    ans_min = min_id;
                    ans_second = second_id;
                } else if (cur_len == ans_len) {
                    if (min_id < ans_min) {
                        ans_min = min_id; ans_second = second_id;
                    } else if (min_id == ans_min) {
                        if (second_id < ans_second) {
                            ans_second = second_id;
                        }
                    }
                }
                delete right_cor;
            };

            do_search(map1, &cor1);
            do_search(map2, &cor2);
            do_search(map3, &cor3);
            do_search(map4, &cor4);
        }
        return {ans_min, ans_second};
    }
};

const vector<int> explode(const string& s, const char& c)
{
    string buff{""};
    vector<int> v;

    for(auto n:s)
    {
        if(n != c && n != '[' && n != ']') buff+=n; else
            if(n == c && buff != "") { v.push_back(stoi(buff)); buff = ""; }
    }
    if(buff != "") v.push_back(stoi(buff));

    return v;
}

int main()
{
    vector<vector<int>> points;
    string s;
    getline(cin, s, ']');
    while (s != "") {
        cout<<s.size()<<"-"<<s<<endl;
        vector<int> temp{explode(s, ',')};
        points.push_back(temp);
        getline(cin, s, ']');
    }
    Solution sol;
    vector<int> ans = sol.bestLine(points);
    cout<<"ans: {"<<ans[0]<<","<<ans[1]<<"}"<<endl;
    return 0;
}
