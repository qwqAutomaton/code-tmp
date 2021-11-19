#include <iostream>
#define forinblock(_i, _num) for (int _i = getL(_num), __r = getR(_num); _i <= __r; _i++)

const int MAXB = 510, MAXN = 120010, BLEN = 300;

struct node
{
    int root, cnt;
} g[MAXB][MAXN];
int n, q;
int block[MAXN], max[MAXN], tag[MAXN];
int pre[MAXN], val[MAXN];
int a[MAXN];
inline int getL(int num) { return (num - 1) * BLEN + 1; }
inline int getR(int num) { return num * BLEN; }
inline int root(int x) { return x == pre[x] ? x : pre[x] = root(pre[x]); }
inline void pushdown(int num)
{
    for (int i = getL(num), __r = getR(num); i <= __r; i++)
    {
        a[i] = val[root(i)];
        g[num][a[i]].cnt = g[num][a[i]].root = 0;
        a[i] -= tag[num];
    }
    tag[num] = 0;
    for (int i = getL(num), __r = getR(num); i <= __r; i++)
        pre[i] = 0;
}
inline void buildblock(int num)
{
    tag[num] = max[num] = 0;
    for (int i = getL(num), __r = getR(num); i <= __r; i++)
    {
        max[num] = std::max(max[num], a[i]);
        g[num][a[i]].cnt++;
        if (g[num][a[i]].root)
            pre[i] = g[num][a[i]].root;
        else
            val[i] = a[i],
            g[num][a[i]].root = pre[i] = i;
    }
}
inline void merge(int num, int x, int y)
{
    node &a = g[num][x], &b = g[num][y];
    if (b.root)
        pre[a.root] = b.root;
    else
        b.root = a.root, val[a.root] = y;
    b.cnt += a.cnt;
    a.cnt = a.root = 0;
}
inline void addtag(int num, int v)
{
    if (v <= max[num] - tag[num] - v)
    {
        for (int i = tag[num] + 1; i <= tag[num] + v; i++)
            if (g[num][i].root)
                merge(num, i, i + v);
        tag[num] += v;
    }
    else
    {
        for (int i = max[num]; i > tag[num] + v; i--)
            if (g[num][i].root)
                merge(num, i, i - v);
        max[num] = std::min(max[num], tag[num] + v);
    }
}
inline void modify(int l, int r, int x)
{
    int lblock = block[l], rblock = block[r];
    pushdown(lblock);
    if (lblock ^ rblock)
    {
        pushdown(rblock);
        int lblockr = getR(lblock), rblockl = getL(rblock);
        for (; l <= lblockr; l++)
            if (a[l] > x)
                a[l] -= x;
        for (; r >= rblockl; r--)
            if (a[r] > x)
                a[r] -= x;
        for (int blk = lblock + 1; blk <= rblock - 1; blk++)
            addtag(blk, x);
        buildblock(lblock);
        buildblock(rblock);
    }
    else
    {
        for (; l <= r; l++)
            if (a[l] > x)
                a[l] -= x;
        buildblock(lblock);
    }
}
inline int query(int l, int r, int x)
{
    int lblock = block[l], rblock = block[r], res = 0;
    if (lblock ^ rblock)
    {
        int lblockr = getR(lblock), rblockl = getL(rblock);
        for (; l <= lblockr; l++)
            if (val[root(l)] - tag[lblock] == x)
                res++;
        for (; r >= rblockl; r--)
            if (val[root(r)] - tag[rblock] == x)
                res++;
        for (int blk = lblock + 1; blk <= rblock - 1; blk++)
            if (x + tag[blk] <= 100000)
                res += g[blk][x + tag[blk]].cnt;
    }
    else
    {
        for (; l <= r; l++)
            if (val[root(l)] - tag[lblock] == x)
                res++;
    }
    return res;
}
int main()
{
    freopen("in", "r", stdin);
    freopen("ans", "w", stdout);
    std::ios::sync_with_stdio(false);
    std::cin >> n >> q;
    for (int i = 1; i <= n; i++)
    {
        std::cin >> a[i];
        block[i] = (i - 1) / BLEN + 1;
    }
    for (int i = block[1]; i <= block[n]; i++)
        buildblock(i);
    for (int i = 1, op, l, r, x; i <= q; i++)
    {
        std::cin >> op >> l >> r >> x;
        if (op == 1)
            modify(l, r, x);
        else
            std::cout << query(l, r, x) << std::endl;
    }
    return 0;
}