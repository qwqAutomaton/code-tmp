#include <iostream>
#include <vector>

const int MAXN = 100010;
struct vertex
{
    int pre, dep, size, hson, top, dfn;
    std::vector<int> to;
} ver[MAXN];
struct node
{
    int l, r;
    int lTag, rTag, tot;
    int lazy;
} seg[MAXN << 2];
int rnk[MAXN], dfn = 0, tag = 1;
void preproc(int cur)
{
    ver[cur].dep = ver[ver[cur].pre].dep + 1;
    ver[cur].size = 1;
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
    ver[cur].dfn = ++dfn;
    rnk[dfn] = cur;
    if (!ver[cur].hson)
        return;
    decomp(ver[cur].hson, top);
    for (auto i : ver[cur].to)
        if (i != ver[cur].pre && i != ver[cur].hson)
            decomp(i, i);
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


