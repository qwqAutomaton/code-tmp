#include <cstring>
#include <iostream>
#include <algorithm>
namespace sol
{
    int money[110], vis[250010];
    int main()
    {
        int n, cnt = 0;
        std::cin >> n;
        for (int i = 1; i <= n; i++)
            std::cin >> money[i];
        std::sort(money + 1, money + 1 + n);
        vis[0] = 1;
        for (int i = 1; i <= n; i++)
        {
            if (vis[money[i]])
                continue;
            for (int j = money[i]; j <= 250000; j++)
                vis[j] |= vis[j - money[i]];
            cnt++;
        }
        std::cout << cnt << std::endl;
        return 0;
    }
}
int main()
{
    freopen("money.in", "r", stdin);
    freopen("money.out", "w", stdout);
    int t;
    std::cin >> t;
    while (t--)
    {
        memset(sol::vis, 0, sizeof(sol::vis));
        sol::main();
    }
    return 0;
}