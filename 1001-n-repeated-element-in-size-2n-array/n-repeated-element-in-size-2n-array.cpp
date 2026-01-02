class Solution {
public:
    int repeatedNTimes(vector<int>& nums) {
        unordered_set<int> seen;
        for (int x : nums) {
            if (seen.count(x)) {
                return x;   // repeated element
            }
            seen.insert(x);
        }
        return -1; // not needed as per constraints
    }
};
