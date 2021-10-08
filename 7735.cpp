#include <iostream>
#include <cstring>
#include <vector>
const int MAXN = 100010;
struct vertex
{
    int top, dep, pre, size, dfn, hson;
    int val; // colour
    std::vector<int> to;
} ver[MAXN];
struct node
{
    int l, r;
    int val, left, right, lazy;
} seg[MAXN << 2];
int dfntot = 0, valtot = 0;
void preproc(int cur, int dep = 1)
{
    ver[cur].dep = dep;
    ver[cur].hson = 0;
    ver[cur].size = 1;
    for (auto i : ver[cur].to)
    {
        if (i == ver[cur].pre)
            continue;
        ver[i].pre = cur;
        preproc(i, dep + 1);
        ver[cur].size += ver[i].size;
        if (ver[i].size > ver[ver[cur].hson].size)
            ver[cur].hson = i;
    }
}
void decompose(int cur, int top = 1)
{
    ver[cur].top = top;
    ver[cur].dfn = ++dfntot;
    if (!ver[cur].hson)
        return;
    decompose(ver[cur].hson, top);
    for (auto i : ver[cur].to)
        if (i != ver[cur].hson && i != ver[cur].pre)
            decompose(i, i);
}
inline void pushup(int cur)
{
    seg[cur].val = seg[cur << 1].val + seg[cur << 1 | 1].val + (seg[cur << 1].right && seg[cur << 1].right == seg[cur << 1 | 1].left ? 1 : 0);
}
inline void pushdown(int cur)
{
    if (seg[cur].lazy)
    {
        seg[cur << 1].val = seg[cur << 1].r - seg[cur << 1].l;
        seg[cur << 1 | 1].val = seg[cur << 1 | 1].r - seg[cur << 1 | 1].l;
        seg[cur << 1].lazy =
            seg[cur << 1 | 1].lazy =
            seg[cur << 1].left =
            seg[cur << 1].right =
            seg[cur << 1 | 1].left =
            seg[cur << 1 | 1].right =
            seg[cur].lazy;
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
void modify(int cur, int l, int r, int c)
{
    if (l <= seg[cur].l && seg[cur].r <= r)
    {
        seg[cur].left = seg[cur].right = seg[cur].lazy = c;
        seg[cur].val = seg[cur].r - seg[cur].l + 1;
        return;
    }
    int mid = seg[cur].l + seg[cur].r >> 1;
    pushdown(cur);
    if (l <= mid)
        modify(cur << 1, l, r, c);
    if (r > mid)
        modify(cur << 1 | 1, l, r, c);
    pushup(cur);
}
int query(int cur, int l, int r)
{
    if (l <= seg[cur].l && seg[cur].r <= r)
        return seg[cur].val;
    pushdown(cur);
    int mid = seg[cur].l + seg[cur].r >> 1, ans = 0;
    if (l <= mid)
        ans += query(cur << 1, l, r);
    if (r > mid)
        ans += query(cur << 1 | 1, l, r);
    if (seg[cur << 1].right == seg[cur << 1 | 1].left)
        ans++;
    pushup(cur);
    return ans;
}
void modify(int u, int v, int c)
{
    while (ver[u].top != ver[v].top)
    {
        if (ver[ver[u].top].dep < ver[ver[v].top].dep)
            std::swap(u, v);
        modify(1, ver[ver[u].top].dfn, ver[u].dfn, c);
        u = ver[ver[u].top].pre;
    }
    if (ver[u].dep < ver[v].dep)
        std::swap(u, v);
    modify(1, ver[v].dfn, ver[u].dfn, c);
}
int query(int u, int v)
{
    int ans = 0;
    while (ver[u].top != ver[v].top)
    {
        if (ver[ver[u].top].dep < ver[ver[v].top].dep)
            std::swap(u, v);
        ans += query(1, ver[ver[u].top].dfn, ver[u].dfn);
        u = ver[ver[u].top].pre;
    }
    if (ver[u].dep < ver[v].dep)
        std::swap(u, v);
    ans += query(1, ver[v].dfn, ver[u].dfn);
    return ans;
}
void clear()
{
    memset(seg, 0, sizeof(seg));
    memset(ver, 0, sizeof(ver));
    valtot = dfntot = 0;
}
void solve()
{
    clear();
    int n, m;
    std::cin >> n >> m;
    for (int i = 1, u, v; i < n; i++)
    {
        std::cin >> u >> v;
        ver[u].to.push_back(v);
        ver[v].to.push_back(u);
    }
    preproc(1);
    decompose(1);
    build(1, 1, n);
    for (int i = 1, op, x, y; i <= m; i++)
    {
        std::cin >> op >> x >> y;
        switch (op)
        {
        case 1:
            modify(x, y, ++valtot);
            break;
        case 2:
            std::cout << query(x, y) << std::endl;
            break;
        default:
            std::cerr << "Fak See See Eff!\n";
            exit(-1);
            break;
        }
    }
}
int main()
{
    int t;
    std::cin >> t;
    while (t--)
        solve();
    return 0;
}

