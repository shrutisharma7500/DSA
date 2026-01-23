class Solution {
public:
    int minimumPairRemoval(vector<int>& nums) {
        int n = nums.size();
        if (n <= 1) return 0;

        vector<long long> val(nums.begin(), nums.end());
        vector<int> L(n), R(n);
        vector<bool> alive(n, true);

        for (int i = 0; i < n; i++) {
            L[i] = i - 1;
            R[i] = (i + 1 < n ? i + 1 : -1);
        }

        // Count initial decreasing adjacent pairs
        int bad = 0;
        for (int i = 0; i + 1 < n; i++) {
            if (val[i] > val[i + 1]) bad++;
        }

        priority_queue<
            pair<long long,int>,
            vector<pair<long long,int>>,
            greater<>
        > pq;

        for (int i = 0; i + 1 < n; i++)
            pq.push({val[i] + val[i + 1], i});

        int ops = 0;

        while (!pq.empty() && bad > 0) {
            auto [s, i] = pq.top(); pq.pop();
            int j = R[i];
            if (j == -1 || !alive[i] || !alive[j]) continue;
            if (val[i] + val[j] != s) continue;

            int li = L[i], rj = R[j];

            // Remove old bad contributions
            if (li != -1 && val[li] > val[i]) bad--;
            if (val[i] > val[j]) bad--;
            if (rj != -1 && val[j] > val[rj]) bad--;

            // Merge
            val[i] += val[j];
            alive[j] = false;
            ops++;

            R[i] = rj;
            if (rj != -1) L[rj] = i;

            // Add new bad contributions
            if (li != -1 && val[li] > val[i]) bad++;
            if (rj != -1 && val[i] > val[rj]) bad++;

            // Push updated pairs
            if (li != -1) pq.push({val[li] + val[i], li});
            if (rj != -1) pq.push({val[i] + val[rj], i});
        }

        return ops;
    }
};
