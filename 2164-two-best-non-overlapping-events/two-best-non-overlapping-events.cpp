class Solution {
public:
    int maxTwoEvents(vector<vector<int>>& events) {
        // Sort by end time
        sort(events.begin(), events.end(),
             [](const vector<int>& a, const vector<int>& b) {
                 return a[1] < b[1];
             });

        int n = events.size();
        
        // Prefix max of values
        vector<int> maxValueUpTo(n);
        maxValueUpTo[0] = events[0][2];

        for (int i = 1; i < n; i++) {
            maxValueUpTo[i] = max(maxValueUpTo[i - 1], events[i][2]);
        }

        int answer = 0;

        for (int i = 0; i < n; i++) {
            int start = events[i][0];
            int value = events[i][2];

            // Binary search: last event with end < start
            int l = 0, r = i - 1, idx = -1;
            while (l <= r) {
                int mid = (l + r) / 2;
                if (events[mid][1] < start) {
                    idx = mid;
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
            }

            // Option 1: take only this event
            answer = max(answer, value);

            // Option 2: take this + best previous
            if (idx != -1) {
                answer = max(answer, value + maxValueUpTo[idx]);
            }
        }

        return answer;
    }
};
