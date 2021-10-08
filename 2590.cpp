#include <iostream>
#include <vector>
#include <functional>
struct vertex
{
    int top, dep, size, pre, hson, dfn;
    int val;
    std::vector<int> next;
} ver[30010];
struct node
{
    int l, r;
    int max, sum, lazy;
    node(int l = 0, int r = 0)
        : l(l), r(r), max(0), sum(0), lazy(0) {}
} seg[120010];
int dfntot = 0, rnk[30010];
void dfs(int cur, int dep = 1)
{
    ver[cur].dep = dep;
    ver[cur].size = 1;
    ver[cur].hson = 0;
    for (auto i : ver[cur].next)
    {
        if (i == ver[cur].pre)
            continue;
        ver[i].pre = cur;
        dfs(i, dep + 1);
        ver[cur].size += ver[i].size;
        if (ver[i].size > ver[ver[cur].hson].size)
            ver[cur].hson = i;
    }
}
void sfd(int cur, int top = 1)
{
    ver[cur].top = top;
    ver[cur].dfn = ++dfntot;
    rnk[dfntot] = cur;
    if (!ver[cur].hson)
        return;
    sfd(ver[cur].hson, top);
    for (auto i : ver[cur].next)
        if (i != ver[cur].hson && i != ver[cur].pre)
            sfd(i, i);
}
inline void pushdown(int cur)
{
    if (seg[cur].lazy)
    {
        seg[cur << 1].lazy += seg[cur].lazy;
        seg[cur << 1 | 1].lazy += seg[cur].lazy;
        seg[cur << 1].sum += (seg[cur << 1].r - seg[cur << 1].l + 1) * seg[cur].lazy;
        seg[cur << 1 | 1].sum += (seg[cur << 1 | 1].r - seg[cur << 1 | 1].l +1) * seg[cur].lazy;
        seg[cur << 1].max += seg[cur].lazy;
        seg[cur << 1 | 1].max += seg[cur].lazy;
        seg[cur].lazy = 0;
    }
}
inline void pushup(int cur)
{
    seg[cur].max = std::max(seg[cur << 1].max, seg[cur << 1 | 1].max);
    seg[cur].sum = seg[cur << 1].sum + seg[cur << 1 | 1].sum;
}
void build(int cur, int l, int r)
{
    seg[cur] = node(l, r);
    if (l == r)
    {
        seg[cur].sum = seg[cur].max = ver[rnk[l]].val;
        return;
    }
    int mid = l + r >> 1;
    build(cur << 1, l, mid);
    build(cur << 1 | 1, mid + 1, r);
    pushup(cur);
}
void modify(int cur, int pos, int v)
{
    if (seg[cur].l == seg[cur].r)
    {
        seg[cur].max = seg[cur].sum = v;
        return;
    }
    pushdown(cur);
    if (pos <= seg[cur].l + seg[cur].r >> 1)
        modify(cur << 1, pos, v);
    else
        modify(cur << 1 | 1, pos, v);
    pushup(cur);
}
int qsum(int cur, int l, int r)
{
    if (l <= seg[cur].l && seg[cur].r <= r)
        return seg[cur].sum;
    int mid = seg[cur].l + seg[cur].r >> 1;
    int ans = 0;
    pushdown(cur);
    if (l <= mid)
        ans += qsum(cur << 1, l, r);
    if (r > mid)
        ans += qsum(cur << 1 | 1, l, r);
    pushup(cur);
    return ans;
}
int qmax(int cur, int l, int r)
{
    if (l <= seg[cur].l && seg[cur].r <= r)
        return seg[cur].max;
    pushdown(cur);
    int mid = seg[cur].l + seg[cur].r >> 1;
    int ans = -1919810;
    if (l <= mid)
        ans = std::max(ans, qmax(cur << 1, l, r));
    if (r > mid)
        ans = std::max(ans, qmax(cur << 1 | 1, l, r));
    pushup(cur);
    return ans;
}
inline void modify(int pos, int val) { modify(1, ver[pos].dfn, val); }
inline int qPath(int u, int v, std::function<int(int, int)> upd, std::function<int(int, int, int)> qry, int initval = -1919810)
{
    int ans = initval;
    while (ver[u].top != ver[v].top)
    {
        if (ver[ver[u].top].dep < ver[ver[v].top].dep)
            std::swap(u, v);
        ans = upd(qry(1, ver[ver[u].top].dfn, ver[u].dfn), ans);
        u = ver[ver[u].top].pre;
    }
    if (ver[u].dep < ver[v].dep)
        std::swap(u, v);
    ans = upd(qry(1, ver[v].dfn, ver[u].dfn), ans);
    return ans;
}
inline int qSum(int u, int v) { return qPath(u, v, [](int a, int b) -> int { return a + b; }, qsum, 0); }
inline int qMax(int u, int v) { return qPath(u, v, std::max<int>, qmax); }
int main()
{
    int n, q;
    std::cin >> n;
    for (int i = 1, u, v; i < n; i++)
    {
        std::cin >> u >> v;
        ver[u].next.push_back(v);
        ver[v].next.push_back(u);
    }
    for (int i = 1; i <= n; i++)
        std::cin >> ver[i].val;
    dfs(1, 1);
    sfd(1, 1);
    build(1, 1, n);
    std::cin >> q;
    for (int i = 1, u, v; i <= q; i++)
    {
        std::string str;
        std::cin >> str >> u >> v;
        if (str == "CHANGE")
            modify(u, v);
        else if (str == "QMAX")
            std::cout << qMax(u, v) << std::endl;
        else if (str == "QSUM")
            std::cout << qSum(u, v) << std::endl;
        else
        {
            std::cerr << "Fuck CCF!\n";
            return -1;
        }
    }
    return 0;
}    

