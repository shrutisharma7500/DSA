class Solution {
public:
    long long maximumProfit(vector<int>& prices, int k) {
        const long long NEG = -1e18;

        // dp[t][state]
        // state: 0 = free, 1 = holding long, 2 = holding short
        vector<vector<long long>> dp(k + 1, vector<long long>(3, NEG));
        dp[0][0] = 0;

        for (int price : prices) {
            auto next = dp;

            for (int t = 0; t <= k; t++) {
                // From free
                if (dp[t][0] != NEG) {
                    next[t][1] = max(next[t][1], dp[t][0] - price); // buy
                    next[t][2] = max(next[t][2], dp[t][0] + price); // short sell
                }

                // From holding long → sell (complete transaction)
                if (t < k && dp[t][1] != NEG) {
                    next[t + 1][0] = max(next[t + 1][0], dp[t][1] + price);
                }

                // From holding short → buy back (complete transaction)
                if (t < k && dp[t][2] != NEG) {
                    next[t + 1][0] = max(next[t + 1][0], dp[t][2] - price);
                }
            }

            dp = next;
        }

        long long ans = 0;
        for (int t = 0; t <= k; t++) {
            ans = max(ans, dp[t][0]);
        }
        return ans;
    }
};
