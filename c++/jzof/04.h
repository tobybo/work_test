class Solution {
public:
    int binarySearch(vector<int> &vec, target) {
        int left = 0;
        int right = vec.size() - 1;
        while (left <= right) {
			int mid = (left + right) / 2;
			if (vec[mid] == target)	{
                return true;
			}
            if (vec[mid] > target) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return false;
    }

    bool findNumberIn2DArray(vector<vector<int>>& matrix, int target) {
        for (int i = 0; i < matrix.size(); ++i) {
            if(binarySearch(matrix[i], target)) return true;
        }
        return false;
    }
};
