#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
struct Queries
{
    int l, r;
    int x;
    int op, ans;
} qs[500010];
int a[1000010];
namespace Block2
{
    int val[1000010], root[120010], size[120010], pre[1000010], max, tag, l, r;
    int find(int x)
    {
        while (x ^ pre[x])
            x = pre[x] = pre[pre[x]];
        return x;
    }
    void merge(int u, int v) // merge two values U and V, u -> v
    {
        if (root[v])
            pre[root[u]] = root[v];
        else
            val[root[v] = root[u]] = v;
        size[v] += size[u];
        root[u] = size[u] = 0;
    }
    void addTag(int val) // globally decrease <val> at the block
    {
        if (2 * val <= max - tag)
        {
            for (int i = tag; i <= tag + val; i++)
                if (root[i])
                    merge(i, i + val);
            tag += val;
        }
        else
        {
            for (int i = max; i > tag + val; i--)
                if (root[i])
                    merge(i, i - val);
            max = std::min(max, tag + val);
        }
    }
    void pushdown()
    {
        for (int i = l; i <= r; i++)
        {
            a[i] = val[find(i)];
            size[a[i]] = root[a[i]] = 0;
            a[i] -= tag;
        }
        tag = 0;
        memset(pre + l, 0, sizeof(int) * (r - l + 1));
    }
    void buildup()
    {
        max = tag = 0;
        for (int i = l; i <= r; i++)
        {
            max = std::max(max, a[i]);
            size[a[i]]++;
            if (root[a[i]])
                pre[i] = root[a[i]];
            else
                val[root[a[i]] = i] = a[pre[i] = i];
        }
    }
    inline void modify(int l, int r, int val)
    {
        if (l <= Block2::l && Block2::r <= r)
            addTag(val);
        else
        {
            pushdown();
            for (int i = std::max(l, Block2::l); i <= std::min(r, Block2::r); i++)
                if (a[i] > val)
                    a[i] -= val;
            buildup();
        }
    }
    inline int query(int l, int r, int x)
    {
        if (x + tag > 100001)
            return 0;
        if (l <= Block2::l && Block2::r <= r)
            return size[x + tag];
        int ret = 0;
        for (int i = std::max(l, Block2::l); i <= std::min(r, Block2::r); i++)
            if (val[find(i)] - tag == x)
                ret++;
        return ret;
    }
}
const int BLKLEN = 1000;
int lpos[1010], rpos[1010];
namespace IO
{
#define S 1310720
    static char wbuf[S];
    static unsigned wpos = 0;
#define ptc(x) ((wpos == 1310720) ? (fwrite(wbuf, 1, 1310720, stdout), wpos = 1, wbuf[0] = x) : (wbuf[wpos++] = x))
    inline void print(int cur)
    {
        static char buf[10];
        int top = 0;
        do
        {
            buf[++top] = (cur % 10) ^ 48;
            cur /= 10;
        } while (cur);
        while (top)
            ptc(buf[top--]);
    }
#undef S
}
int main()
{
#ifdef VSCODE_DEBUG
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);
    int n, m;
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++)
        std::cin >> a[i];
    for (int i = 1; i <= m; i++)
        std::cin >> qs[i].op >> qs[i].l >> qs[i].r >> qs[i].x;
    int blocks = (n - 1) / BLKLEN + 1;
    for (int i = 1; i <= blocks; i++)
        lpos[i] = BLKLEN * (i - 1) + 1, rpos[i] = BLKLEN * i;
    rpos[blocks] = n;
    for (int i = 1; i <= blocks; i++)
    {
        Block2::l = lpos[i], Block2::r = rpos[i];
        memset(Block2::root, 0, sizeof(Block2::root));
        memset(Block2::size, 0, sizeof(Block2::size));
        Block2::buildup();
        for (int j = 1; j <= m; j++)
        {
            if (qs[j].r < lpos[i] || qs[j].l > rpos[i])
                continue;
            if (qs[j].op == 1)
                Block2::modify(qs[j].l, qs[j].r, qs[j].x);
            else
            {
                if (qs[j].x + Block2::tag > 100001)
                    continue;
                if (qs[j].l <= Block2::l && Block2::r <= qs[j].r)
                    qs[j].ans += Block2::size[Block2::tag + qs[j].x];
                else
                    for (int L = std::max(qs[j].l, Block2::l), R = std::min(qs[j].r, Block2::r); L <= R; L++)
                        qs[j].ans += Block2::val[Block2::find(L)] - Block2::tag == qs[j].x;
            }
        }
    }
    using namespace IO;
    for (int i = 1; i <= m; i++)
        if (!(qs[i].op & 1))
        {
            print(qs[i].ans);
            ptc('\n');
        }
    if (wpos)
        fwrite(wbuf, 1, wpos, stdout);
    return 0;
}