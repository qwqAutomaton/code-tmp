#include <iostream>
#include <cstring>
#include <queue>
struct Edge
{
    int to, dis, next;
    Edge(int to = 0, int dis = 0, int next = 0) : to(to), dis(dis), next(next) {}
} E[400010];
int d[100010], now[100010], head[100010], etot = 1, t;
inline void add(int u, int v, int d)
{
    E[++etot] = Edge(v, d, head[u]);
    head[u] = etot;
}
void dfs(int cur, int pre = -1)
{
    bool flag = false;
    for (int i = head[cur]; i; i = E[i].next)
        if (E[i].to != pre)
        {
            E[i ^ 1].dis = 0;
            dfs(E[i].to, cur);
            flag = true;
        }
    if (!flag)
    {
        add(cur, t, 0x3f3f3f3f);
        add(t, cur, 0);
    }
}
bool bfs(int s, int t)
{
    memset(d, -1, sizeof(d));
    std::queue<int> q;
    q.push(s);
    d[s] = 1, now[s] = head[s];
    while (!q.empty())
    {
        int cur = q.front();
        q.pop();
        if (cur == t)
            return true;
        for (int i = head[cur]; i; i = E[i].next)
            if (E[i].dis > 0 && d[E[i].to] == -1)
            {
                d[E[i].to] = d[cur] + 1;
                now[E[i].to] = head[E[i].to];
                q.push(E[i].to);
            }
    }
    return false;
}
int getflow(int s, int t, int flow = 0x7f7f7f7f)
{
    if (s == t || !flow)
        return flow;
    int ret = 0;
    for (int i = now[s]; i; i = E[i].next, now[s] = i)
        if (E[i].dis > 0 && d[E[i].to] == d[s] + 1)
        {
            int tmp = getflow(E[i].to, t, std::min(flow, E[i].dis));
            if (!tmp)
                d[E[i].to] = -1;
            E[i].dis -= tmp;
            E[i ^ 1].dis += tmp;
            ret += tmp;
            flow -= tmp;
        }
    return ret;
}
int main()
{
    int n, s;
    std::cin >> n >> s;
    for (int i = 1, u, v, c; i < n; i++)
    {
        std::cin >> u >> v >> c;
        add(u, v, c);
        add(v, u, c);
    }
    t = n + 1;
    dfs(s);
    int ans = 0;
    while (bfs(s, t))
        ans += getflow(s, t);
    std::cout << ans << std::endl;
    return 0;
}