#include <iostream>
#include <cstring>
#include <queue>
#define int long long
namespace Flow
{
    struct Edge
    {
        int to, dis, next;
        Edge(int to = 0, int dis = 0, int next = 0) : to(to), dis(dis), next(next) {}
    } E[240010];
    int head[1500];
    int etot = 1;
    inline void add(int u, int v, int d)
    {
        E[++etot] = Edge(v, d, head[u]);
        head[u] = etot;
    }
    namespace EdmondsKarpEK
    {
        int pre[1500], dis[1500];
        bool vis[1500];
        std::queue<int> q;
        bool bfs(int s, int t)
        {
            std::clog << "BFS..." << std::endl;
            memset(vis, 0, sizeof(vis));
            while (!q.empty())
                q.pop();
            vis[s] = 1, dis[s] = 2147483647;
            q.push(s);
            while (!q.empty())
            {
                int cur = q.front();
                q.pop();
                for (int i = head[cur]; i; i = E[i].next)
                {
                    if (E[i].dis <= 0)
                        continue;
                    int nxt = E[i].to;
                    if (vis[nxt])
                        continue;
                    pre[nxt] = i, vis[nxt] = 1;
                    dis[nxt] = std::min(dis[cur], E[i].dis);
                    if (nxt == t)
                        return true;
                    q.push(nxt);
                }
            }
            return false;
        }
        int update(int s, int t)
        {
            std::clog << "Updating..." << std::endl;
            int x = t;
            while (x != s)
            {
                int p = pre[x];
                E[p].dis -= dis[t];
                E[p ^ 1].dis += dis[t];
                x = E[p ^ 1].to;
            }
            return dis[t];
        }
        int EK(int s, int t)
        {
            int ans = 0;
            while (bfs(s, t))
                ans += update(s, t);
            return ans;
        }
    }
    namespace Dinic
    {
        int d[1500], now[1500];
        std::queue<int> q;
        bool bfs(int s, int t)
        {
            memset(d, 0x3f, sizeof(d));
            while (!q.empty())
                q.pop();
            q.push(s);
            d[s] = 1, now[s] = head[s];
            while (!q.empty())
            {
                int cur = q.front();
                q.pop();
                if (cur == t)
                    return true;
                for (int i = head[cur]; i; i = E[i].next)
                    if (E[i].dis > 0 && d[E[i].to] >= 2147483647)
                    {
                        d[E[i].to] = d[cur] + 1;
                        now[E[i].to] = head[E[i].to];
                        q.push(E[i].to);
                    }
            }
            return false;
        }
        int dfs(int s, int t, int dis)
        {
            if (s == t)
                return dis;
            int ret = 0;
            for (int i = now[s]; i; i = E[i].next)
            {
                now[s] = i;
                if (E[i].dis > 0 && d[E[i].to] == d[s] + 1)
                {
                    int tmp = dfs(E[i].to, t, std::min(dis, E[i].dis));
                    if (!tmp)
                        d[E[i].to] = -1;
                    E[i].dis -= tmp;
                    E[i ^ 1].dis += tmp;
                    ret += tmp;
                    dis -= tmp;
                }
            }
            return ret;
        }
        int dinic(int s, int t)
        {
            int ret = 0;
            while (bfs(s, t))
                ret += dfs(s, t, 0x3f3f3f3f3f3f3f3fLL);
            return ret;
        }
    }
    using Dinic::dinic;
    using EdmondsKarpEK::EK;
}
int flag[1500][1500];
signed main()
{
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m, s, t;
    std::cin >> n >> m >> s >> t;
    for (int i = 1, u, v, c; i <= m; i++)
    {
        std::cin >> u >> v >> c;
        if (!flag[u][v])
        {
            Flow::add(u, v, c);
            Flow::add(v, u, 0);
            flag[u][v] = Flow::etot - 1;
        }
        else
            Flow::E[flag[u][v]].dis += c;
    }
    std::cout << Flow::dinic(s, t) << std::endl;
    return 0;
}