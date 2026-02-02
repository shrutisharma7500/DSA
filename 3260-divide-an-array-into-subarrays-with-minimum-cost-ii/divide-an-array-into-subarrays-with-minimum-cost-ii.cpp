class Solution {
public:
    long long minimumCost(vector<int>& nums, int k, int dist) {
        int n = nums.size();
        int need = k - 1;
        
        multiset<pair<int,int>> small, large; // {value, index}
        long long sumSmall = 0;
        
        auto balance = [&]() {
            while (small.size() > need) {
                auto it = prev(small.end());
                sumSmall -= it->first;
                large.insert(*it);
                small.erase(it);
            }
            while (small.size() < need && !large.empty()) {
                auto it = large.begin();
                sumSmall += it->first;
                small.insert(*it);
                large.erase(it);
            }
        };
        
        auto addElement = [&](int val, int idx) {
            small.insert({val, idx});
            sumSmall += val;
            balance();
        };
        
        auto removeElement = [&](int val, int idx) {
            auto it = small.find({val, idx});
            if (it != small.end()) {
                sumSmall -= val;
                small.erase(it);
            } else {
                large.erase(large.find({val, idx}));
            }
            balance();
        };
        
        // Build initial window [1, min(1+dist, n-1)]
        for (int i = 1; i <= min(n - 1, 1 + dist); i++) {
            addElement(nums[i], i);
        }
        
        long long ans = LLONG_MAX;
        if (small.size() == need) {
            ans = nums[0] + sumSmall;
        }
        
        // Slide window: each iteration moves left by 1
        for (int left = 2; left < n; left++) {
            // Remove element at left-1
            removeElement(nums[left - 1], left - 1);
            
            // Add element at left+dist if it exists
            int newRight = left + dist;
            if (newRight < n) {
                addElement(nums[newRight], newRight);
            }
            
            if (small.size() == need) {
                ans = min(ans, nums[0] + sumSmall);
            }
        }
        
        return ans;
    }
};