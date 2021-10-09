#include <iostream>
#include <vector>
#define int long long

const int MAXN = 1000010, ROOT = 1;
using ll = long long;

struct vertex
{
    int top, pre, hson, size, dep, dfn;
    int val;
    std::vector<int> to;
} ver[MAXN];
struct node
{
    int l, r;
    ll sum, lazy;
} seg[MAXN << 2];
int rnk[MAXN], dfntot = 0;
inline void pushup(int cur)
{
    seg[cur].sum = seg[cur << 1].sum + seg[cur << 1 | 1].sum;
}
inline void pushdown(int cur)
{
    if (!seg[cur].lazy)
        return;
    seg[cur << 1].sum += seg[cur].lazy * (seg[cur << 1].r - seg[cur << 1].l + 1);
    seg[cur << 1 | 1].sum += seg[cur].lazy * (seg[cur << 1 | 1].r - seg[cur << 1 | 1].l + 1);
    seg[cur << 1].lazy += seg[cur].lazy;
    seg[cur << 1 | 1].lazy += seg[cur].lazy;
    seg[cur].lazy = 0;
}
void build(int cur, int l, int r)
{
    seg[cur].l = l;
    seg[cur].r = r;
    seg[cur].lazy = 0;
    if (l == r)
    {
        seg[cur].sum = ver[rnk[l]].val;
        return;
    }
    int mid = seg[cur].l + seg[cur].r >> 1;
    build(cur << 1, l, mid);
    build(cur << 1 | 1, mid + 1, r);
    pushup(cur);
}
void preproc(int cur)
{
    ver[cur].size = 1;
    ver[cur].hson = 0;
    ver[cur].dep = ver[ver[cur].pre].dep + 1;
    for (auto i : ver[cur].to)
    {
        if (i == ver[cur].pre)
            continue;
        ver[i].pre = cur;
        preproc(i);
        ver[cur].size += ver[i].size;
        if (ver[i].size >= ver[ver[cur].hson].size)
            ver[cur].hson = i;
    }
}
void decomp(int cur, int top)
{
    ver[cur].top = top;
    ver[cur].dfn = ++dfntot;
    rnk[dfntot] = cur;
    if (!ver[cur].hson)
        return;
    decomp(ver[cur].hson, top);
    for (auto i : ver[cur].to)
        if (i != ver[cur].pre && i != ver[cur].hson)
            decomp(i, i);
}
void add(int cur, int l, int r, int v)
{
    if (l <= seg[cur].l && seg[cur].r <= r)
    {
        seg[cur].sum += v * (seg[cur].r - seg[cur].l + 1);
        seg[cur].lazy += v;
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
        return seg[cur].sum;
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
inline void addSubtree(int x, int v)
{
    add(1, ver[x].dfn, ver[x].dfn + ver[x].size - 1, v);
}
inline ll queryPath(int x)
{
    ll ans = 0;
    while (ver[x].top != ROOT)
    {
        ans += query(1, ver[ver[x].top].dfn, ver[x].dfn);
        x = ver[ver[x].top].pre;
    }
    ans += query(1, ver[ROOT].dfn, ver[x].dfn);
    return ans;
}
signed main()
{
    int n, m;
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++)
        std::cin >> ver[i].val;
    for (int i = 1, u, v; i < n; i++)
    {
        std::cin >> u >> v;
        ver[u].to.push_back(v);
        ver[v].to.push_back(u);
    }
    preproc(ROOT);
    decomp(ROOT, ROOT);
    build(1, 1, n);
    for (int i = 1, op, x, a; i <= m; i++)
    {
        std::cin >> op >> x;
        switch (op)
        {
        case 1:
            std::cin >> a;
            add(1, ver[x].dfn, ver[x].dfn, a);
            break;
        case 2:
            std::cin >> a;
            addSubtree(x, a);
            break;
        case 3:
            std::cout << queryPath(x) << std::endl;
            break;
        }
    }
    return 0;
}

