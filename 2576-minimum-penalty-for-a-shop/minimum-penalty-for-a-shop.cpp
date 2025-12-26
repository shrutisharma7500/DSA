class Solution {
public:
    int bestClosingTime(string customers) {
        int n = customers.size();
        
        // Count total Y initially (penalty if shop closes at time 0)
        int penalty = 0;
        for (char c : customers) {
            if (c == 'Y') penalty++;
        }
        
        int minPenalty = penalty;
        int bestTime = 0;
        
        // Try closing after each hour
        for (int i = 0; i < n; i++) {
            if (customers[i] == 'Y') {
                penalty--;      // shop stays open, avoids penalty
            } else {
                penalty++;      // shop open but no customers
            }
            
            if (penalty < minPenalty) {
                minPenalty = penalty;
                bestTime = i + 1;
            }
        }
        
        return bestTime;
    }
};
