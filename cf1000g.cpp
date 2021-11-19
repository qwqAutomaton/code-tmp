// Contest: Educational Codeforces Round 46
// Problem name: Two-Paths (然而第六章的 A 面并没有草莓)
// Problem number: CF1000G (loj #6699)
// Time limit: 1000ms
// Memory limit: 512MB
// Author: qwqAutomaton
// Language: C++
// Version: GNU / C++14
// n <= 3e5, q <= 5e5
//

#pragma GCC optimize(2)
#pragma GCC optimize("unroll-loops")
#include <iostream>
#include <vector>
#define int long long
const int MAXN = 3e5 + 10;

struct edge
{
    int to, z1, z2; // z1: from->to, z2: to->from
    edge(int a, int b, int c) : to(a), z1(b), z2(c) {}
};
int dfn[MAXN], rnk[MAXN], dfntot = 0;
int size[MAXN], hson[MAXN], top[MAXN];
int pre[MAXN], dep[MAXN], val[MAXN];  // cur->fa, fa->cur, val
int f[MAXN], g[MAXN], c[MAXN];        // f: cur->subtree, g: cur->all, c: contribute to pre
int fs[MAXN], dis1[MAXN], dis2[MAXN]; // partial sum, cur->fa, fa->cur
int dr1[MAXN], dr2[MAXN];             // partial sum * 2
std::vector<edge> to[MAXN];
void dfs1(int cur)
{
    dep[cur] = dep[pre[cur]] + 1;
    size[cur] = 1, hson[cur] = 0;
    for (auto i : to[cur])
    {
        if (i.to == pre[cur])
            continue;
        pre[i.to] = cur;
        dis1[i.to] = i.z2;
        dis2[i.to] = i.z1;
        dfs1(i.to);
        size[cur] += size[i.to];
        if (size[i.to] > size[hson[cur]])
            hson[cur] = i.to;
    }
}
void dfs2(int cur, int top)
{
    dfn[cur] = ++dfntot;
    ::top[cur] = top, rnk[dfntot] = cur;
    if (!hson[cur])
        return;
    dfs2(hson[cur], top);
    for (auto i : to[cur])
        if (i.to != pre[cur] && i.to != hson[cur])
            dfs2(i.to, i.to);
}
void dp1(int cur)
{
    f[cur] = val[cur];
    for (auto i : to[cur])
    {
        if (i.to == pre[cur])
            continue;
        dp1(i.to);
        c[i.to] = std::max(0LL, f[i.to] - i.z1 - i.z2);
        f[cur] += c[i.to];
    }
}
void dp2(int cur)
{
    for (auto i : to[cur])
    {
        if (i.to == pre[cur])
            continue;
        g[i.to] = f[i.to] + std::max(0LL, g[cur] - c[i.to] - i.z1 - i.z2);
        dp2(i.to);
    }
}
void getPartialSum(int cur)
{
    dr1[cur] = dr1[pre[cur]] + dis1[cur];
    dr2[cur] = dr2[pre[cur]] + dis2[cur];
    fs[cur] = fs[pre[cur]] + f[cur] - c[cur];
    for (auto i : to[cur])
        if (i.to != pre[cur])
            getPartialSum(i.to);
}
int LCA(int u, int v)
{
    while (top[u] != top[v])
    {
        if (dep[top[u]] < dep[top[v]])
            std::swap(u, v);
        u = pre[top[u]];
    }
    return dep[u] < dep[v] ? u : v;
}
signed main()
{
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int n, q;
    std::cin >> n >> q;
    for (int i = 1; i <= n; i++)
        std::cin >> val[i];
    for (int i = 1, u, v, z; i < n; i++)
    {
        std::cin >> u >> v >> z;
        to[u].emplace_back(v, z, z);
        to[v].emplace_back(u, z, z);
    }
    pre[1] = 0;
    dfs1(1);
    dfs2(1, 1);
    dp1(1);
    g[1] = f[1];
    dp2(1);
    getPartialSum(1);
    for (int i = 1, u, v; i <= q; i++)
    {
        std::cin >> u >> v;
        int lca = LCA(u, v);
        int dist = dr1[u] + dr2[v] - dr1[lca] - dr2[lca];
        int qnq = fs[u] + fs[v] - fs[lca] * 2 + g[lca];
        std::cout << qnq - dist << '\n';
        // std::clog << "Dist(" << u << " -> " << v << ") = " << dist << std::endl;
        // std::clog << "LCA(" << u << ", " << v << ") = " << lca << std::endl;
    }
    return 0;
}