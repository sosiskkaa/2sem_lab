#include <iostream>
#include <vector>

using namespace std;

long long bPow(long long x, long long y, const int MOD)
{
    if (y == 1)
        return x;
    if (y % 2 == 1)
        return bPow(x, y - 1, MOD) * x % MOD;
    else
    {
        long long temp = bPow(x, y / 2, MOD);
        return temp * temp % MOD;
    }
}

int main()
{
    int n, k;

    cin >> n >> k;
    vector<long long> Fact(n + 1);
    Fact[0] = Fact[1] = 1;

    const int MOD = 1000000007;

    for (int i = 2; i <= n; i++)
    {
        Fact[i] = (i * Fact[i - 1]) % MOD;
    }

    long long den = (Fact[k] * Fact[n - k]) % MOD;

    long long res = (Fact[n] * bPow(den, MOD - 2, MOD)) % MOD;

    cout << res;

    return 0;
}
