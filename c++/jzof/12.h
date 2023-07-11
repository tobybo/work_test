// 给定一个 m x n 二维字符网格 board 和一个字符串单词 word 。如果 word 存在于网格中，返回 true ；否则，返回 false 。
//
// 单词必须按照字母顺序，通过相邻的单元格内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。同一个单元格内的字母不允许被重复使用。
//
//
//
// 例如，在下面的 3×4 的矩阵中包含单词 "ABCCED"（单词中的字母已标出）。
//
//
//
//
//
// 示例 1：
//
// 输入：board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCCED"
// 输出：true
// 示例 2：
//
// 输入：board = [["a","b"],["c","d"]], word = "abcd"
// 输出：false
//
//
// 提示：
//
// m == board.length
// n = board[i].length
// 1 <= m, n <= 6
// 1 <= word.length <= 15
// board 和 word 仅由大小写英文字母组成

class Solution {
public:
    bool findWorld(vector<vector<char>>& board, int i, int j, string &world, int p, char **vis) {
        if (vis[i][j]) return false;
        int m = board.size();
        int n = board[0].size();
        if (world[p] != board[i][j]) return false;
        if (p + 1 == world.size()) return true;
        vis[i][j] = 1;
        bool left, up, right, down;
        // 左
        if (j - 1 >= 0) left = findWorld(board, i, j - 1, world, p + 1, vis);
        // 上
        if (i - 1 >= 0) up = findWorld(board, i - 1, j, world, p + 1, vis);
        // 右
        if (j + 1 < n) right = findWorld(board, i, j + 1, world, p + 1, vis);
        // 下
        if (i + 1 < m) down = findWorld(board, i + 1, j, world, p + 1, vis);
        vis[i][j] = 0;
        return left || up || right || down;
    }

    bool exist(vector<vector<char>>& board, string word) {
        int m = board.size();
        int n = board[0].size();
        int k = word.size();
        if (k > m * n) return false;
		char vis[m][n];
        memset(vis, 0, sizeof(vis));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (board[i][j] == word[0]) {
                    if (findWorld(board, i, j, world, 0, (char **)vis)) {
                        return true;
                    }
                }
            }
        }
    }
};
