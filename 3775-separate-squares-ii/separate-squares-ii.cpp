class Solution {
public:
    struct Event {
        long long y, x1, x2;
        int type;
        bool operator<(const Event& other) const {
            return y < other.y;
        }
    };

    vector<long long> xs;
    vector<long long> seg, cover;

    void pushUp(int node, int l, int r) {
        if (cover[node] > 0) {
            seg[node] = xs[r] - xs[l];
        } else if (l + 1 == r) {
            seg[node] = 0;
        } else {
            seg[node] = seg[node * 2] + seg[node * 2 + 1];
        }
    }

    void update(int node, int l, int r, int ql, int qr, int val) {
        if (ql >= r || qr <= l) return;
        if (ql <= l && r <= qr) {
            cover[node] += val;
            pushUp(node, l, r);
            return;
        }
        int mid = (l + r) / 2;
        update(node * 2, l, mid, ql, qr, val);
        update(node * 2 + 1, mid, r, ql, qr, val);
        pushUp(node, l, r);
    }

    double separateSquares(vector<vector<int>>& squares) {
        vector<Event> events;

        for (auto& s : squares) {
            long long x = s[0], y = s[1], l = s[2];
            events.push_back({y, x, x + l, +1});
            events.push_back({y + l, x, x + l, -1});
            xs.push_back(x);
            xs.push_back(x + l);
        }

        sort(events.begin(), events.end());
        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());

        int n = xs.size();
        seg.assign(4 * n, 0);
        cover.assign(4 * n, 0);

        unordered_map<long long, int> xid;
        for (int i = 0; i < n; i++) xid[xs[i]] = i;

        long double totalArea = 0;
        vector<long double> stripArea;
        vector<long long> stripY;
        vector<long long> stripXLen;

        long long prevY = events[0].y;
        long long curXLen = 0;

        int i = 0;
        while (i < events.size()) {
            long long y = events[i].y;
            long long dy = y - prevY;

            if (dy > 0) {
                stripArea.push_back((long double)curXLen * dy);
                stripY.push_back(prevY);
                stripXLen.push_back(curXLen);
                totalArea += (long double)curXLen * dy;
            }

            while (i < events.size() && events[i].y == y) {
                update(1, 0, n - 1, xid[events[i].x1], xid[events[i].x2], events[i].type);
                i++;
            }

            curXLen = seg[1];
            prevY = y;
        }

        long double half = totalArea / 2.0;
        long double acc = 0;

        for (int i = 0; i < stripArea.size(); i++) {
            if (acc + stripArea[i] >= half) {
                if (stripXLen[i] == 0) return (double)stripY[i];
                return (double)(stripY[i] + (half - acc) / stripXLen[i]);
            }
            acc += stripArea[i];
        }

        return (double)stripY.back();
    }
};
