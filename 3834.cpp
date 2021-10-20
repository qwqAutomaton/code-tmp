#include <algorithm>
#include <iostream>
#include <cstring>
const int MAXN = 200010;
namespace psgt
{
struct node
{
    int lson, rson;
    int l, r;
    int sum;
} pool[MAXN * 25];
int root[MAXN], tail = 0;
int apply()
{
    if (++tail < MAXN)
        return tail;
    return -1;
}
int build(int l, int r)
{
    int cur = apply();
    pool[cur].l = l;
    pool[cur].r = r;
    if (l == r)
        return cur;
    int mid = l + r >> 1;
    pool[cur].lson = build(l, mid);
    pool[cur].rson = build(mid + 1, r);
    return cur;
}
int add(int cur, int pos, int val)
{
    if (pool[cur].l == pool[cur].r)
    {
        pool[cur].sum += val;
        return;
    }
    int mid = pool[cur].l + pool[cur].r >> 1;
    int qwq = apply();
    if (pos <= mid)
    {
        pool[qwq].l = l;
        pool[qwq].r = mid;
        pool[qwq].rson = pool[cur].rson;
        pool[qwq].lson = add(pool[cur].lson, pos, val);
    }
    else
    {
        pool[qwq].l = mid + 1;
        pool[qwq].r = r;
        pool[qwq].lson = pool[cur].lson;
        pool[qwq].rson = add(pool[cur].rson, pos, val);
    }
    return qwq;
}
int query(int )
}
int raw[MAXN], tmp[MAXN], rnk[MAXN];
int main()
{
    int n, q;
    std::cin >> n >> q;
    for (int i = 1; i <= n; i++)
    {
        std::cin >> raw[i];
        tmp[i] = raw[i];
    }
    std::sort(tmp + 1, tmp + 1 + n);
    int m = std::unique(tmp + 1, tmp + 1 + n) - tmp - 1;
    psgt::root[0] = psgt::build(1, m);
    for (int i = 1; i <= n; i++)
        psgt::root[i] = psgt::add(psgt::root[i - 1], std::lower_bound(tmp + 1, tmp + m + 1, raw[i]), 1);
    return 0;
}

