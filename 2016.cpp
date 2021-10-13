#include <iostream>
#include <vector>
const int MAXN = 1510;
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
        g[0][cur] *= g[1][i];
        if (f[1][i] < f[0][i])
        {
            f[1][cur] += f[1][i];
            g[1][cur] *= g[1][i];
        }
        else
        {
            f[1][cur] += f[0][i];
            g[1][cur] *= g[0][i] * (f[1][i] == f[0][i] ? g[1][i] : 1);
        }
    }
}
int main()
{
    int n;
    std::cin >> n;
    if (n == 1)
    {
        std::cout << "1\n";
        return 0;
    }
    for (int i = 1, index, k; i <= n; i++)
    {
        std::cin >> index >> k;
        index++;
        for (int t; k; k--)
        {
            std::cin >> t;
            to[index].push_back(t + 1);
            to[t + 1].push_back(index);
        }
    }
    dp(1, -1);
    std::cout << std::min(f[1][1], f[0][1]);
    return 0;
}

