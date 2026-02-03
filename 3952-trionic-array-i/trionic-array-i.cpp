class Solution {
public:
    bool isTrionic(vector<int>& nums) {
        int n = nums.size();
        if (n < 4) return false;

        int i = 0;

        // 1️⃣ strictly increasing
        while (i + 1 < n && nums[i] < nums[i + 1]) {
            i++;
        }
        if (i == 0) return false; // no increasing part

        // 2️⃣ strictly decreasing
        int p = i;
        while (i + 1 < n && nums[i] > nums[i + 1]) {
            i++;
        }
        if (i == p) return false; // no decreasing part

        // 3️⃣ strictly increasing
        int q = i;
        while (i + 1 < n && nums[i] < nums[i + 1]) {
            i++;
        }
        if (i == q) return false; // no final increasing part

        // must consume entire array
        return i == n - 1;
    }
};
