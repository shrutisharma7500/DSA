class Solution {
public:
    static constexpr long long INF = (long long)4e18;
    static constexpr long long MOD1 = 1000000007;
    static constexpr long long MOD2 = 1000000009;
    static constexpr long long BASE = 91138233;

    struct Hash {
        long long h1, h2;
        bool operator==(const Hash& o) const {
            return h1 == o.h1 && h2 == o.h2;
        }
    };

    Hash buildHash(const string& s) {
        long long a = 0, b = 0;
        for (char c : s) {
            a = (a * BASE + c) % MOD1;
            b = (b * BASE + c) % MOD2;
        }
        return {a, b};
    }

    Hash getSubHash(
        const vector<long long>& h1,
        const vector<long long>& h2,
        const vector<long long>& p1,
        const vector<long long>& p2,
        int l, int r
    ) {
        long long x1 = (h1[r + 1] - h1[l] * p1[r - l + 1] % MOD1 + MOD1) % MOD1;
        long long x2 = (h2[r + 1] - h2[l] * p2[r - l + 1] % MOD2 + MOD2) % MOD2;
        return {x1, x2};
    }

    long long minimumCost(
        string source, string target,
        vector<string>& original,
        vector<string>& changed,
        vector<int>& cost
    ) {
        int n = source.size();

        /* -------- map strings to ids -------- */
        unordered_map<string, int> id;
        int idx = 0;
        auto getId = [&](const string& s) {
            if (!id.count(s)) id[s] = idx++;
            return id[s];
        };

        for (int i = 0; i < original.size(); i++) {
            getId(original[i]);
            getId(changed[i]);
        }

        int m = idx;
        vector<string> rev(m);
        for (auto& [s, i] : id) rev[i] = s;

        /* -------- Floyd–Warshall -------- */
        vector<vector<long long>> dist(m, vector<long long>(m, INF));
        for (int i = 0; i < m; i++) dist[i][i] = 0;

        for (int i = 0; i < original.size(); i++) {
            int u = id[original[i]];
            int v = id[changed[i]];
            dist[u][v] = min(dist[u][v], (long long)cost[i]);
        }

        for (int k = 0; k < m; k++)
            for (int i = 0; i < m; i++)
                for (int j = 0; j < m; j++)
                    if (dist[i][k] < INF && dist[k][j] < INF)
                        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

        /* -------- rolling hash prep -------- */
        vector<long long> p1(n + 1, 1), p2(n + 1, 1);
        for (int i = 1; i <= n; i++) {
            p1[i] = p1[i - 1] * BASE % MOD1;
            p2[i] = p2[i - 1] * BASE % MOD2;
        }

        vector<long long> hs1(n + 1, 0), hs2(n + 1, 0);
        vector<long long> ht1(n + 1, 0), ht2(n + 1, 0);

        for (int i = 0; i < n; i++) {
            hs1[i + 1] = (hs1[i] * BASE + source[i]) % MOD1;
            hs2[i + 1] = (hs2[i] * BASE + source[i]) % MOD2;
            ht1[i + 1] = (ht1[i] * BASE + target[i]) % MOD1;
            ht2[i + 1] = (ht2[i] * BASE + target[i]) % MOD2;
        }

        /* -------- build ALL valid transformations after Floyd -------- */
        unordered_map<int, vector<pair<Hash, Hash>>> trans;
        unordered_map<int, vector<long long>> transCost;

        for (int u = 0; u < m; u++) {
            for (int v = 0; v < m; v++) {
                if (dist[u][v] == INF) continue;
                if (rev[u].size() != rev[v].size()) continue;

                int len = rev[u].size();
                trans[len].push_back({buildHash(rev[u]), buildHash(rev[v])});
                transCost[len].push_back(dist[u][v]);
            }
        }

        /* -------- DP -------- */
        vector<long long> dp(n + 1, INF);
        dp[n] = 0;

        for (int i = n - 1; i >= 0; i--) {
            // no-op
            if (source[i] == target[i]) {
                dp[i] = min(dp[i], dp[i + 1]);
            }

            for (auto& [len, vec] : trans) {
                int j = i + len - 1;
                if (j >= n) continue;

                Hash hs = getSubHash(hs1, hs2, p1, p2, i, j);
                Hash ht = getSubHash(ht1, ht2, p1, p2, i, j);

                for (int k = 0; k < vec.size(); k++) {
                    if (hs == vec[k].first && ht == vec[k].second) {
                        dp[i] = min(dp[i], transCost[len][k] + dp[j + 1]);
                    }
                }
            }
        }

        return dp[0] == INF ? -1 : dp[0];
    }
};
