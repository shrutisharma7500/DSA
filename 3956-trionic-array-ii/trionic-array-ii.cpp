class Solution {
public:
    long long maxSumTrionic(vector<int>& nums) {
        int n = nums.size();
        const long long NEG = -4e18;

        vector<long long> inc0(n, NEG), dec1(n, NEG), inc2(n, NEG);
        long long result = NEG;

        for (int i = 1; i < n; i++) {

            // State 0: strictly increasing (length >= 2)
            if (nums[i] > nums[i - 1]) {
                inc0[i] = nums[i - 1] + nums[i];          // start new
                if (inc0[i - 1] > NEG)
                    inc0[i] = max(inc0[i], inc0[i - 1] + nums[i]); // extend
            }

            // State 1: strictly decreasing
            if (nums[i] < nums[i - 1]) {
                if (inc0[i - 1] > NEG)
                    dec1[i] = inc0[i - 1] + nums[i];     // start dec
                if (dec1[i - 1] > NEG)
                    dec1[i] = max(dec1[i], dec1[i - 1] + nums[i]); // extend
            }

            // State 2: strictly increasing again
            if (nums[i] > nums[i - 1]) {
                if (dec1[i - 1] > NEG)
                    inc2[i] = dec1[i - 1] + nums[i];    // start final inc
                if (inc2[i - 1] > NEG)
                    inc2[i] = max(inc2[i], inc2[i - 1] + nums[i]); // extend
            }

            result = max(result, inc2[i]);
        }

        return result;
    }
};
