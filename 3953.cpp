#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
struct edge
{
    int to, dis;
    edge(int a, int b) : to(a), dis(b) {}
};
int f[100010][110];
int n, m, k, p;
std::vector<edge> to[100010], ot[100010];
int dis[100010]; // mindis(1->u);
bool vis[100010][110];
int dp(int cur, int lim)
{
    std::clog << "DP(" << cur << ", " << lim << ")...\n";
    if (vis[cur][lim])
        return -1;
    if (~f[cur][lim])
        return f[cur][lim];
    vis[cur][lim] = 1;
    int res = cur == 1;
    for (auto i : ot[cur])
    {
        int v = i.to;
        int tmp = dis[cur] + lim - dis[v] - i.dis;
        if (tmp < 0)
            continue;
        int qwq = dp(v, tmp);
        if (~qwq)
            (res += qwq) %= p;
        else
            return -1;
    }
    vis[cur][lim] = 0;
    return f[cur][lim] = res % p;
}
void spfa()
{
    memset(dis, 0x3f, sizeof(dis));
    static bool v[100010];
    memset(v, 0, sizeof(v));
    std::queue<int> q;
    while (!q.empty())
        q.pop();
    q.push(1), v[1] = 1, dis[1] = 0;
    while (!q.empty())
    {
        int cur = q.front();
        q.pop(), v[cur] = 0;
        for (auto i : to[cur])
            if (dis[i.to] > dis[cur] + i.dis)
            {
                dis[i.to] = dis[cur] + i.dis;
                if (!v[i.to])
                    q.push(i.to), v[i.to] = 1;
            }
    }
}
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
        memset(f, -1, sizeof(f));
        memset(vis, 0, sizeof(vis));
        memset(dis, 0x3f, sizeof(dis));
        std::cin >> n >> m >> k >> p;
        for (int i = 1; i <= n; i++)
            to[i].clear(), ot[i].clear();
        for (int i = 1, u, v, d; i <= m; i++)
        {
            std::cin >> u >> v >> d;
            to[u].push_back(edge(v, d));
            ot[v].push_back(edge(u, d));
        }
        spfa();
        std::cout << dp(n, k) << '\n';
    }
    return 0;
}