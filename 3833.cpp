#include <iostream>
#include <vector>
const int MAXN = 100010;
using ll = long long;
struct vers
{
    int top, pre, size, dep, hson, dfn;
    ll val;
    std::vector<int> nxt;
    vers(): top(0), pre(0), size(0), dep(0), hson(0), dfn(0), val(0) { nxt.clear(); } 
} ver[MAXN];
struct node
{
    int l, r;
    ll val, lazy;
    node(): l(0), r(0), val(0), lazy(0) {} 
} seg[MAXN << 2];
int dfntot = 0;
void dfs1(int cur, int dep)
{
    ver[cur].dep = dep;
    ver[cur].hson = 0;
    ver[cur].size = 1;
    for (auto i : ver[cur].nxt)
    {
        if (i == ver[cur].pre)
            continue;
        ver[i].pre = cur;
        dfs1(i, dep + 1);
        ver[cur].size += ver[i].size;
        if (ver[i].size > ver[ver[cur].hson].size)
            ver[cur].hson = i;
    }
}
void dfs2(int cur, int top)
{
    ver[cur].dfn = ++dfntot;
    ver[cur].top = top;
    if (!ver[cur].hson)
        return;
    dfs2(ver[cur].hson, top);
    for (auto i : ver[cur].nxt)
        if (i != ver[cur].pre && i != ver[cur].hson)
            dfs2(i, i);
}
inline void pushup(int cur) { seg[cur].val = seg[cur << 1].val + seg[cur << 1 | 1].val; }
inline void pushdown(int cur)
{
    if (seg[cur].lazy)
    {
        seg[cur << 1].lazy += seg[cur].lazy;
        seg[cur << 1 | 1].lazy += seg[cur].lazy;
        seg[cur << 1].val += (seg[cur << 1].r - seg[cur << 1].l + 1) * seg[cur].lazy;
        seg[cur << 1 | 1].val += (seg[cur << 1 | 1].r - seg[cur << 1 | 1].l + 1) * seg[cur].lazy;
        seg[cur].lazy = 0;
    }
}
void build(int cur, int l, int r)
{
    seg[cur].l = l;
    seg[cur].r = r;
    if (l == r)
        return;
    int mid = l + r >> 1;
    build(cur << 1, l, mid);
    build(cur << 1 | 1, mid + 1, r);
}
void add(int cur, int l, int r, ll v)
{
    if (l <= seg[cur].l && seg[cur].r <= r)
    {
        seg[cur].lazy += v;
        seg[cur].val += (seg[cur].r - seg[cur].l + 1) * v;
        return;
    }
    pushdown(cur);
    int mid = seg[cur].l + seg[cur].r >> 1;
    if (l <= mid)
        add(cur << 1, l, r, v);
    if (r > mid)
        add(cur << 1 | 1, l, r, v);
    pushup(cur);
}
ll query(int cur, int l, int r)
{
    if (l <= seg[cur].l && seg[cur].r <= r)
        return seg[cur].val;
    ll ans = 0;
    int mid = seg[cur].l + seg[cur].r >> 1;
    pushdown(cur);
    if (l <= mid)
        ans += query(cur << 1, l, r);
    if (r > mid)
        ans += query(cur << 1 | 1, l, r);
    pushup(cur);
    return ans;
}
ll qSubtree(int u) { return query(1, ver[u].dfn, ver[u].dfn + ver[u].size - 1); }
void aPath(int u, int v, ll k)
{
    while (ver[u].top != ver[v].top)
    {
        if (ver[ver[u].top].dep < ver[ver[v].top].dep)
            std::swap(u, v);
        add(1, ver[ver[u].top].dfn, ver[u].dfn, k);
        u = ver[ver[u].top].pre;
    }
    if (ver[u].dep < ver[v].dep)
        std::swap(u, v);
    add(1, ver[v].dfn, ver[u].dfn, k);
}
int main()
{
    int n;
    std::cin >> n;
    for (int i = 1, u, v; i < n; i++)
    {
        std::cin >> u >> v;
        ver[u + 1].nxt.push_back(v + 1);
  //      ver[v + 1].nxt.push_back(u + 1);
    }
    dfs1(1, 1);
    dfs2(1, 1);
    build(1, 1, n);
    int m;
    std::cin >> m;
    for (int i = 1; i <= m; i++)
    {
        char op;
        ll u, v, d;
        std::cin >> op;
        switch(op)
        {
            case 'A':
                std::cin >> u >> v >> d;
                aPath(u + 1, v + 1, d);
                break;
            case 'Q':
                std::cin >> u;
                std::cout << qSubtree(u + 1) << '\n';
                break;
            default:
                std::cerr << "Fuck CCF!\n";
                return -1;
        }
    }
    return 0;
}

