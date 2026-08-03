#include <iostream>
using namespace std;

long long power(long long base, long long exp, long long mod) {
    long long res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return res;
}

// O(log n) Time Complexity
long long sumOfPowers(long long x, long long n, long long mod) {
    if (n == 0) return 1;
    if (n % 2 == 0) {
        // لو الأُس زوجي: x^0 + x * (x^0 + ... + x^(n-1))
        return (1 + (x % mod) * sumOfPowers(x, n - 1, mod)) % mod;
    } else {
        // لو الأُس فردي: (1 + x^((n+1)/2)) * (sumOfPowers(n/2))
        long long half = sumOfPowers(x, n / 2, mod);
        long long p = power(x, (n + 1) / 2, mod);
        return (half * (1 + p)) % mod;
    }
}

int main() {
    long long x = 3, n = 4, mod = 1e9 + 7;
    // 3^0 + 3^1 + 3^2 + 3^3 + 3^4 = 1 + 3 + 9 + 27 + 81 = 121
    cout << sumOfPowers(x, n, mod) << endl; 
    return 0;
}
