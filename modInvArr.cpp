const int MOD = 1e9 + 7;
const int MAXN = 1000000;

vector<long long> fac(MAXN + 1), invFac(MAXN + 1);

long long fast_pow(long long a, long long b) {
    long long res = 1;
    while (b) {
        if (b & 1)
            res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

void init() {
    fac[0] = 1;
    for (int i = 1; i <= MAXN; i++)
        fac[i] = fac[i - 1] * i % MOD;

    invFac[MAXN] = fast_pow(fac[MAXN], MOD - 2);

    for (int i = MAXN; i >= 1; i--)
        invFac[i - 1] = invFac[i] * i % MOD;
}
