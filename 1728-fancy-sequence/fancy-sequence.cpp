class Fancy {
public:
    const long MOD = 1e9 + 7;
    
    vector<long long> arr;
    long long mul = 1;
    long long add = 0;

    long long modInverse(long long x) {
        long long res = 1;
        long long p = MOD - 2;
        while(p) {
            if(p & 1) res = res * x % MOD;
            x = x * x % MOD;
            p >>= 1;
        }
        return res;
    }

    Fancy() {}

    void append(int val) {
        long long x = (val - add + MOD) % MOD;
        x = x * modInverse(mul) % MOD;
        arr.push_back(x);
    }

    void addAll(int inc) {
        add = (add + inc) % MOD;
    }

    void multAll(int m) {
        mul = (mul * m) % MOD;
        add = (add * m) % MOD;
    }

    int getIndex(int idx) {
        if(idx >= arr.size()) return -1;
        return (arr[idx] * mul % MOD + add) % MOD;
    }
};