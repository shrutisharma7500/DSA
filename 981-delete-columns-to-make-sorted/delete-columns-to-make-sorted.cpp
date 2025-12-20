class Solution {
public:
    int minDeletionSize(vector<string>& strs) {
        int n = strs.size();
        int m = strs[0].size();
        int deleteCount = 0;

        // Check each column
        for (int col = 0; col < m; col++) {
            for (int row = 0; row < n - 1; row++) {
                if (strs[row][col] > strs[row + 1][col]) {
                    deleteCount++;
                    break; // No need to check further rows for this column
                }
            }
        }
        return deleteCount;
    }
};
