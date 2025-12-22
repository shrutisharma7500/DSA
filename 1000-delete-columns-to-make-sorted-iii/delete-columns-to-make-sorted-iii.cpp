class Solution {
public:
    int minDeletionSize(vector<string>& strs) {
        int n = strs.size();
        int m = strs[0].size();
        
        vector<int> dp(m, 1);  // dp[j] = max kept columns ending at j
        
        for (int j = 0; j < m; j++) {
            for (int i = 0; i < j; i++) {
                bool valid = true;
                
                // check all rows
                for (int r = 0; r < n; r++) {
                    if (strs[r][i] > strs[r][j]) {
                        valid = false;
                        break;
                    }
                }
                
                if (valid) {
                    dp[j] = max(dp[j], dp[i] + 1);
                }
            }
        }
        
        int maxKeep = *max_element(dp.begin(), dp.end());
        return m - maxKeep;
    }
};
