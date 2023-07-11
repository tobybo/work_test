#include <iostream>
#include <vector>

using namespace std;

int do_opt(vector <vector<int>> rect, int width, int hight, int opt, int x, int y);
int add_count(vector <vector<int>> rect, int width, int hight, int x, int y);

int main() {
    int width,hight;
    int baseNum;
    int optNum;
    vector <int> initList;
    vector <int> optList; // { 0 删除 1 增加 , x, y, ... }

    cin>>width>>hight;
    cin>>baseNum;
    int tempx, tempy;
    for (int i = 0; i < baseNum; ++i) {
        cin>>tempx>>tempy;
        initList.push_back(tempx);
        initList.push_back(tempy);
    }
    cin>>optNum;
    string tempOpt;
    for (int i = 0; i < optNum; ++i) {
        cin>>tempOpt;
        if (tempOpt == "delete") {
            cin>>tempx>>tempy;
            delList.push_back(0);
            delList.push_back(tempx);
            delList.push_back(tempy);
        } else if (tempOpt == "add") {
            cin>>tempx>>tempy;
            delList.push_back(1);
            addList.push_back(tempx);
            addList.push_back(tempy);
        }
    }

    vector <vector<int>> rect(hight, vector<int>(width, 0));
    for (int i = 0; i < initList.size(); ++i) {
        tempx = initList[i];
        if ((i % 2) == 0) {
            tempy = initList[i];
            rect[y][x] = -1; // 基站
        }
    }

    int opt;
    int idx;
    for (int i = 0; i < optList.size(); ++i) {
        idx = (i + 1) % 3;
        switch (idx) {
            case 1:
                opt = optList[i];
                break;
            case 2:
                tempx = optList[i];
                break;
            case 0:
                tempy = optList[i];
                do_opt(rect, width, hight, opt, tempx, tempy);
                break;
        }
    }

    int sum = 0;
    for (int y = 0; y < hight; ++y) {
        for (int x = 0; x < width; ++y) {
            if (rect[y][x] == -1) {
                sum += add_count(rect, width, hight, x, y);
            }
        }
    }

    cout<<sum;

    return sum;
}

int do_opt(vector <vector<int>> rect, int width, int hight, int opt, int x, int y){
    if (opt == 0) {
        for (int cy = y - 1; cy <= y + 1; ++cy) {
            if (cy < 0 || cy >= hight) continue;
            for (int cx = x - 1; cx <= x + 1; ++cx) {
                if (cx < 0 || cx >= width) continue;
                rect[cy][cx] = 0;
            }
        }
    } else if (opt == 1) {
        rect[cy][cx] = -1;
    }
    return 0;
}

int add_count(vector <vector<int>> rect, int width, int hight, int x, int y){
    int sum = 0
    for (int cy = y - 1; cy <= y + 1; ++cy) {
        if (cy < 0 || cy >= hight) continue;
        for (int cx = x - 1; cx <= x + 1; ++cx) {
            if (cx < 0 || cx >= width) continue;
            if (cy == y && cx == x) continue;
            if (rect[cy][cx] == -1) continue;
            sum++;
        }
    }
    return sum;
}

