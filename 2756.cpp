#include <iostream>
#include <cstring>
#include <queue>
const int MAXN = 110, MAXM = 10010;
int head[MAXN], to[MAXM], cap[MAXM], next[MAXM], d[MAXN], now[MAXN], etot = 1;
bool vis[MAXN];
void add(int u, int v, int d)
{
    to[++etot] = v;
    cap[etot] = d;
    next[etot] = head[u];
    head[u] = etot;
}
bool bfs(int s, int t)
{
    memset(vis, 0, sizeof(vis));
    std::queue<int> q;
    q.push(s);
    vis[s] = 1, d[s] = 1, now[s] = head[s];
    while (!q.empty())
    {
        int cur = q.front();
        q.pop();
        if (cur == t)
            return true;
        for (int i = head[cur]; i; i = next[i])
            if (!vis[to[i]] && cap[i] > 0)
            {
                vis[to[i]] = 1, d[to[i]] = d[cur] + 1;
                now[to[i]] = head[to[i]];
                q.push(to[i]);
            }
    }
    return false;
}
int dfs(int s, int t, int flow = 2147483647)
{
    if (s == t || !flow)
        return flow;
    int ret = 0;
    for (int i = now[s]; i; now[s] = i, i = next[i])
        if (cap[i] > 0 && d[to[i]] == d[s] + 1)
        {
            int tmp = dfs(to[i], t, std::min(flow, cap[i]));
            if (!tmp)
                d[to[i]] = -1;
            cap[i] -= tmp, cap[i ^ 1] += tmp;
            ret += tmp, flow -= tmp;
        }
    return ret;
}
int main()
{
    int n, m, s, t;
    std::cin >> m >> n;
    s = n + 1, t = n + 2;
    while (true)
    {
        int u, v;
        std::cin >> u >> v;
        if (u == -1 && v == -1)
            break;
        add(u, v, 0x3f3f3f3f);
        add(v, u, 0);
    }
    for (int i = 1; i <= m; i++)
    {
        add(s, i, 1);
        add(i, s, 0);
    }
    for (int i = m + 1; i <= n; i++)
    {
        add(i, t, 1);
        add(t, i, 0);
    }
    int ans = 0, flow = 0;
    while (bfs(s, t))
        while ((flow = dfs(s, t)))
            ans += flow;
    std::cout << ans << std::endl;
    for (int i = 2; i <= etot; i += 2)
        if (to[i] != s && to[i] != t && to[i ^ 1] != s && to[i ^ 1] != t && cap[i ^ 1] != 0)
            std::cout << to[i ^ 1] << ' ' << to[i] << std::endl;
    return 0;
}

