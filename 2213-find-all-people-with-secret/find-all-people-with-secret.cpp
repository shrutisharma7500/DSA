class Solution {
public:
    vector<int> parent;

    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }

    void unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x != y) parent[y] = x;
    }

    vector<int> findAllPeople(int n, vector<vector<int>>& meetings, int firstPerson) {
        sort(meetings.begin(), meetings.end(),
             [](auto &a, auto &b) { return a[2] < b[2]; });

        vector<bool> knowsSecret(n, false);
        knowsSecret[0] = true;
        knowsSecret[firstPerson] = true;

        int i = 0;
        while (i < meetings.size()) {
            int time = meetings[i][2];

            // Collect all meetings at same time
            vector<int> people;
            int j = i;
            while (j < meetings.size() && meetings[j][2] == time) {
                people.push_back(meetings[j][0]);
                people.push_back(meetings[j][1]);
                j++;
            }

            // Initialize DSU for this time
            parent.clear();
            unordered_map<int, int> idx;
            for (int p : people) idx[p] = p;
            for (auto &kv : idx) parent.push_back(0);

            parent.resize(n);
            for (int p : people) parent[p] = p;

            // Union meetings
            for (int k = i; k < j; k++) {
                unite(meetings[k][0], meetings[k][1]);
            }

            // Track components with secret
            unordered_set<int> goodRoots;
            for (int p : people) {
                if (knowsSecret[p]) {
                    goodRoots.insert(find(p));
                }
            }

            // Spread secret
            for (int p : people) {
                if (goodRoots.count(find(p))) {
                    knowsSecret[p] = true;
                }
            }

            i = j;
        }

        vector<int> result;
        for (int i = 0; i < n; i++) {
            if (knowsSecret[i]) result.push_back(i);
        }
        return result;
    }
};
