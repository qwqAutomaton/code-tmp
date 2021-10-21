#include <iostream>
const int MAXN = 100010, MAXB = 350, BLOCK = 300;
void modify(int l, int r, int x);
int query(int l, int r, int x);
int a[MAXN], pre[MAXN], f[MAXB][MAXN], fa[MAXB][MAXN], block[MAXN], tag[MAXB], max[MAXB], val[MAXN];
inline int getL(int num) { return (num - 1) * BLOCK + 1; }                // OK
inline int getR(int num) { return num * BLOCK; }                          // OK
inline int root(int x) { return x ^ pre[x] ? pre[x] = root(pre[x]) : x; } // OK
inline void initblock(int num)                                            // OK
{
    max[num] = 0;
    int rpos = getR(num);
    tag[num] = 0;
    for (int lpos = getL(num); lpos <= rpos; lpos++)
    {
        max[num] = std::max(max[num], a[lpos]);
        f[num][a[lpos]]++;
        if (fa[num][a[lpos]])
            pre[lpos] = fa[num][a[lpos]];
        else
            pre[lpos] = fa[num][a[lpos]] = lpos, val[lpos] = a[lpos];
    }
}
inline void merge(int b, int x, int y) // x <-> y in block #b // OK
{
    if (fa[b][y])
        pre[fa[b][x]] = fa[b][y];
    else
        fa[b][y] = fa[b][x], val[fa[b][x]] = y;
    f[b][y] += f[b][x];
    f[b][x] = fa[b][x] = 0;
}
inline void pushdown(int x) // OK
{
    int rpos = getR(x);
    for (int lpos = getL(x); lpos <= rpos; lpos++)
    {
        a[lpos] = val[root(lpos)];
        fa[x][a[lpos]] = f[x][a[lpos]] = 0;
        a[lpos] -= tag[x];
    }
    tag[x] = 0;
    for (int lpos = getL(x); lpos <= rpos; lpos++)
        pre[lpos] = 0;
}
inline void addtag(int x, int v) // block #x globally -v // OK
{
    if (v <= max[x] - tag[x] - v)
    {
        for (int i = tag[x] + 1; i <= tag[x] + v; i++)
            if (fa[x][i])
                merge(x, i, i + v);
        tag[x] += v;
    }
    else
    {
        for (int i = max[x]; i > tag[x] + v; i--)
            if (fa[x][i])
                merge(x, i, i - v);
        max[x] = std::min(max[x], tag[x] + v);
    }
}
signed main()
{
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
    std::ios::sync_with_stdio(false);
    int n, m;
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        std::cin >> a[i];
        block[i] = (i - 1) / BLOCK + 1;
    }
    for (int i = block[1]; i <= block[n]; i++)
        initblock(i);
    for (int i = 1, op, l, r, x; i <= m; i++)
    {
        std::cin >> op >> l >> r >> x;
        switch (op)
        {
        case 1:
            modify(l, r, x);
            break;
        case 2:
            std::cout << query(l, r, x) << '\n';
            break;
        default:
            std::cerr << "qwq\n";
            break;
        }
    }
    std::cout.flush();
    return 0;
}
void modify(int l, int r, int x) // OK
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
        for (int b = lblock + 1; b <= rblock - 1; b++)
            addtag(b, x);
        initblock(lblock);
        initblock(rblock);
    }
    else
    {
        for (; l <= r; l++)
            if (a[l] > x)
                a[l] -= x;
        initblock(lblock);
    }
}
int query(int l, int r, int x) // OK
{
    int ans = 0;
    int lblock = block[l], rblock = block[r];
    if (lblock ^ rblock)
    {
        int lblockr = getR(lblock), rblockl = getL(rblock);
        for (; l <= lblockr; l++)
            if (val[root(l)] == x + tag[lblock])
                ans++;
        for (; r >= rblockl; r--)
            if (val[root(r)] == x + tag[rblock])
                ans++;
        for (int b = lblock + 1; b <= rblock - 1; b++)
            if (x + tag[b] <= 100000)
                ans += f[b][x + tag[b]];
    }
    else
        for (; l <= r; l++)
            if (val[root(l)] == x + tag[lblock])
                ans++;
    return ans;
}