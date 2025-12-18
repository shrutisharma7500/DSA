class Solution {
public:
    long long maxProfit(vector<int>& prices, vector<int>& strategy, int k) {
        int n = prices.size();
        
        // Step 1: Base profit
        long long baseProfit = 0;
        for (int i = 0; i < n; i++) {
            baseProfit += 1LL * strategy[i] * prices[i];
        }
        
        // Prefix sum of prices
        vector<long long> prefPrice(n + 1, 0);
        // Prefix sum of original contribution
        vector<long long> prefOrig(n + 1, 0);
        
        for (int i = 0; i < n; i++) {
            prefPrice[i + 1] = prefPrice[i] + prices[i];
            prefOrig[i + 1] = prefOrig[i] + 1LL * strategy[i] * prices[i];
        }
        
        long long bestGain = 0;
        int half = k / 2;
        
        // Step 2: Sliding window
        for (int i = 0; i + k <= n; i++) {
            // Original contribution of window
            long long original = prefOrig[i + k] - prefOrig[i];
            
            // New contribution after modification
            long long secondHalfSum =
                prefPrice[i + k] - prefPrice[i + half];
            
            long long gain = secondHalfSum - original;
            bestGain = max(bestGain, gain);
        }
        
        return baseProfit + bestGain;
    }
};
