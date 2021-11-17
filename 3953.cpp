#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>
namespace Sol
{
    const int MAXN = 1e5 + 10;
    std::vector<int> to[MAXN], invto[MAXN];
    int n, m, k, p;
    void clear()
    {
        n = m = k = p = 0;
        for (int i = 0; i < MAXN; i++)
            to[i].clear(), invto[i].clear();
    }
    int main()
    {
        std::cin >> n >> m >> k >> p;
        for (int i = 1, u, v, d; i <= m; i++)
        {
            std::cin >> u >> v >> d;
            to[u].push_back(v);
            to[v].push_back(u);
        }
        return 0;
    }
}

//

int main()
{
#ifdef VSCODE_DEBUG
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int t;
    std::cin >> t;
    while (t--)
    {
        int ret;
        Sol::clear();
        if ((ret = Sol::main()))
            return ret;
    }
    std::cout << std::flush;
    return 0;
}
