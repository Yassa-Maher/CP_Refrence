vector<long long> primes;
vector<long long> sieve(long long n) {
    vector<bool> isPrime(n + 1, true);
    isPrime[0] = false;
    isPrime[1] = false;
    for (int p = 2; p * p <= n; ++p) {
        if (isPrime[p]) {
            for (int i = p * p; i <= n; i += p)
                isPrime[i] = false;
        }
    }
    for(int i=0 ; i<=n ; i++){
        if(isPrime[i])primes.push_back(i);
    }
    return primes;
}

void fast()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
}

long long gcd(long long a, long long b)
{
    while (b != 0)
    {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}


long long lcm(long long a, long long b)
{
    return (a / gcd(a, b)) * b;
}

auto GetBit(int i, int j)
{
    int mask = 1 << j;
    return (mask & i);
}

long long FastPower(long long x, long long p, long long mod)
{
    long long result = 1 % mod;
    x %= mod;
    while (p > 0)
    {
        if (p & 1)
            result = (result * x) % mod;
        x = (x * x) % mod;
        p >>= 1;
    }
    return result;
}



long long gcd(long long a, long long b)
{
    while (b != 0)
    {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

void addPrimeFactors(long long x, map<long long,int> &freq)
{
    for (long long p = 2; p * p <= x; p++)
    {
        while (x % p == 0)
        {
            freq[p]++;
            x /= p;
        }
    }
    if (x > 1) freq[x]++;
}

void getPrimeFactors_SEIVE(long long x, vector<pair<long long,int>> &factors)
{
    for (long long p = 2; p * p <= x; p++)
    {
        if (x % p == 0)
        {
            int cnt = 0;
            while (x % p == 0)
            {
                x /= p;
                cnt++;
            }
            factors.push_back({p, cnt});
        }
    }
    if (x > 1)
    {
        factors.push_back({x, 1});
    }
}

long long buildNumber(const vector<pair<long long,int>> &factors)
{
    long long result = 1;
    for (auto [prime, power] : factors)
    {
        for (int i = 0; i < power; i++)
        {
            result *= prime;
        }
    }
    return result;
}

long long fastPowLL(long long a, long long b)
{
    long long res = 1;
    a %= M;
    while (b > 0)
    {
        if (b & 1) res = res * a % M;
        a = a * a % M;
        b >>= 1;
    }
    return res;
}

long long mod_inverse(long long a) {
    return fast_pow(a, MOD-2);
}

sort(v.begin(), v.end(), [](auto &x, auto &y) {
        return x.second < y.second;
});

sort(v.begin(), v.end(), [](pair<int,int> a, pair<int,int> b){
    if(a.first == b.first)
        return a.second > b.second;
    return a.first < b.first;
});

sort(v.begin(), v.end(), [](pair<int,int> a, pair<int,int> b){
    return a.second < b.second;
});
