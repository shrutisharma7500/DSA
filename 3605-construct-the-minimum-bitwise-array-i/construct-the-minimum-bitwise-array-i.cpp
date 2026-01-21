class Solution {
public:
    vector<int> minBitwiseArray(vector<int>& nums) {
        vector<int> ans;

        for (int x : nums) {
            // Even numbers are impossible
            if (x % 2 == 0) {
                ans.push_back(-1);
                continue;
            }

            int temp = x;
            int trailingOnes = 0;

            // Count trailing 1s
            while (temp & 1) {
                trailingOnes++;
                temp >>= 1;
            }

            // Remove the highest power of 2 in trailing ones
            ans.push_back(x - (1 << (trailingOnes - 1)));
        }

        return ans;
    }
};
