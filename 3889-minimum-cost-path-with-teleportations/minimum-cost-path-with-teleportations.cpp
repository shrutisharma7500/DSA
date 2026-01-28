class Solution {
public:
    int minCost(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();
        const int INF = 1e9;

        int N = m * n;

        // dist[pos][teleports]
        vector<vector<int>> dist(N, vector<int>(k + 1, INF));

        // collect cells sorted by value
        vector<pair<int,int>> cells; // {value, index}
        cells.reserve(N);
        for (int i = 0; i < N; i++) {
            int r = i / n, c = i % n;
            cells.push_back({grid[r][c], i});
        }
        sort(cells.begin(), cells.end());

        // pointer per teleport layer
        vector<int> ptr(k + 1, 0);

        priority_queue<array<int,3>, vector<array<int,3>>, greater<>> pq;
        pq.push({0, 0, 0}); // cost, pos, teleports
        dist[0][0] = 0;

        int dr[2] = {0, 1};
        int dc[2] = {1, 0};

        while (!pq.empty()) {
            auto [cost, pos, t] = pq.top();
            pq.pop();

            if (cost > dist[pos][t]) continue;
            if (pos == N - 1) return cost;

            int r = pos / n;
            int c = pos % n;

            // normal moves
            for (int d = 0; d < 2; d++) {
                int nr = r + dr[d];
                int nc = c + dc[d];
                if (nr < m && nc < n) {
                    int npos = nr * n + nc;
                    int ncost = cost + grid[nr][nc];
                    if (ncost < dist[npos][t]) {
                        dist[npos][t] = ncost;
                        pq.push({ncost, npos, t});
                    }
                }
            }

            // teleport
            if (t < k) {
                while (ptr[t] < N && cells[ptr[t]].first <= grid[r][c]) {
                    int idx = cells[ptr[t]].second;
                    if (cost < dist[idx][t + 1]) {
                        dist[idx][t + 1] = cost;
                        pq.push({cost, idx, t + 1});
                    }
                    ptr[t]++;
                }
            }
        }

        int ans = INF;
        for (int t = 0; t <= k; t++) {
            ans = min(ans, dist[N - 1][t]);
        }
        return ans;
    }
};
