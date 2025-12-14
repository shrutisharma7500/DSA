class Solution {
public:
    int numberOfWays(string corridor) {
        const int MOD = 1e9 + 7;
        long long ways = 1;
        int seats = 0;
        int plants = 0;

        for (char c : corridor) {
            if (c == 'S') {
                seats++;
                // Every time we finish a pair (except first),
                // multiply ways by (plants + 1)
                if (seats > 2 && seats % 2 == 1) {
                    ways = (ways * (plants + 1)) % MOD;
                    plants = 0;
                }
            } else if (seats >= 2 && seats % 2 == 0) {
                plants++;
            }
        }

        return (seats % 2 == 0 && seats > 0) ? ways : 0;
    }
};
