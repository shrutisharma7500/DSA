class Solution {
public:
    vector<int> minBitwiseArray(vector<int>& nums) {
        vector<int> ans;

        for (int x : nums) {
            // Even numbers are impossible
            if ((x & 1) == 0) {
                ans.push_back(-1);
                continue;
            }

            int k = 0;
            int temp = x;

            // Count trailing 1s
            while ((temp & 1) == 1) {
                k++;
                temp >>= 1;
            }

            // Remove the highest trailing-1 block
            ans.push_back(x - (1 << (k - 1)));
        }

        return ans;
    }
};
