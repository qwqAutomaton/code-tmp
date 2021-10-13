#include <iostream>
#include <cstring>
#include <vector>
const int MAXN = 100020, MOD = 10007;
std::vector<int> to[MAXN];
int f[2][MAXN], g[2][MAXN];
void dp(int cur, int pre)
{
    f[0][cur] = 0;
    f[1][cur] = 1;
    g[0][cur] = g[1][cur] = 1;
    for (auto i : to[cur])
    {
        if (i == pre)
            continue;
        dp(i, cur);
        f[0][cur] += f[1][i];
        (g[0][cur] *= g[1][i]) %= MOD;
        if (f[1][i] < f[0][i])
        {
            f[1][cur] += f[1][i];
            (g[1][cur] *= g[1][i]) %= MOD;
        }
        else
        {
            f[1][cur] += f[0][i];
            if (f[1][i] == f[0][i])
                (g[1][cur] *= g[0][i] + g[1][i]) %= MOD;
            else
                (g[1][cur] *= g[0][i]) %= MOD;
        }
    }
}
int solve()
{
    memset(f, 0, sizeof(f));
    memset(g, 0, sizeof(g));
    int n;
    std::cin >> n;
    for (int i = 0; i <= n; i++)
        to[i].clear();
    for (int i = 1, x, y; i < n; i++)
    {
        std::cin >> x >> y;
        to[x].push_back(y);
        to[y].push_back(x);
    }
    if (n == 1)
    {
        std::cout << "1 1\n";
        return 0;
    }
    dp(1, -1);
    if (f[1][1] < f[0][1])
    {
        std::cout << f[1][1] << ' ' << g[1][1] << '\n';
        return 0;
    }
    else
    {
        std::cout << f[0][1] << ' ';
        if (f[0][1] == f[1][1])
            std::cout << (g[1][1] + g[0][1]) % MOD << '\n';
        else
            std::cout << g[0][1] % MOD << '\n';
        return 0;
    }
    return 0;
}
int main()
{
    int t;
    std::cin >> t;
    while (t--)
        solve();
    return 0;
}

