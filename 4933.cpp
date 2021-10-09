#include <iostream>
const int MAXN = 1010;
const int MOD = 998244353;
int f[MAXN][40010];
int h[MAXN];
int main()
{
    int n;
    std::cin >> n;
    for (int i = 1; i <= n; i++)
        std::cin >> h[i];
    int ans = n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j < i; j++)
            (f[i][h[i] - h[j] + 20000] += f[j][h[i] - h[j] + 20000] + 1) %= MOD;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= 40000; j++)
            (ans += f[i][j]) %= MOD;
    std::cout << ans << std::endl;
    return 0;
}

