#include <iostream>
const int MAXB = 330;
namespace qwq
{
    int a[500010], tag = 0, max, l, r;
    int pre[500010], root[500010], size[500010], val[500010];
    int get(int x) { x ^ pre[x] ? pre[x] = get(pre[x]) : pre[x]; }
    void init()
    {
        tag = max = 0;
        for (int i = l; i <= r; i++)
        {
            max = std::max(max, a[i]);
            size[a[i]]++;
            if (root[a[i]])
                pre[i] = root[a[i]];
            else
            {
                val[i] = a[i];
                root[a[i]] = pre[i] = i;
            }
        }
    }
    void merge(int u, int v)
    {
        if (root[u])
            pre[v] = u;
        else
        {
            root[u] = root[v];
            val[v] = u;
        }
        size[u] += size[v];
        root[v] = size[v] = 0;
    }
    void addTag(int v)
    {
        if (max - tag >= 2 * v)
        {
            for (int i = 1; i <= v; i++)
                if (pre[i + tag])
                    merge(i, i + v);
            tag += v;
        }
        else
        {
            for (int i = max; i > tag + v; i--)
                if (pre[i])
                    merge(i, i - v);
            max = std::max(max, tag + v);
        }
    }
    void pushdown()
    {
        for (int i = l; i <= r; i++)
        {
            a[i] = val[get(i)];
            size[a[i]] = root[a[i]] = 0;
            a[i] -= tag;
        }
        tag = 0;
        for (int i = l; i <= r; i++)
            pre[i] = 0;
    }
}
struct Queries
{
    int op, l, r, x, ans;
    Queries() : op(0), l(0), r(0), x(0), ans(0) {}
} qs[500010];
int n, m;
int main()
{
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++)
        std::cin >> qwq::a[i];
    for (int i = 1; i <= m; i++)
        std::cin >> qs[i].op >> qs[i].l >> qs[i].r >> qs[i].x;
    int blocklen = 300;
    for (int i = 1;; i++)
    {
        int l = (i - 1) * blocklen + 1, r = i * blocklen;
        if (l > n)
            break;
        qwq::l = l;
        qwq::r = r;
        qwq::init();
        for (int i = 1; i <= m; i++)
        {
            if (qs[i].r < l || qs[i].l > r)
                continue;
            if (qs[i].op == 1)
            {
                if (qs[i].l <= l && r <= qs[i].r)
                    qwq::addTag(qs[i].x);
                else if (qs[i].l > l)
                {
                    qwq::pushdown();
                    for (int j = qs[i].l; j <= r; j++)
                        if (qwq::a[i] > qs[i].x)
                            qwq::a[i] -= qs[i].x;
                }
                else if (qs[i].r < r)
                {
                    qwq::pushdown();
                    for (int j = qs[i].r; j >= l; j--)
                        if (qwq::a[i] > qs[i].x)
                            qwq::a[i] -= qs[i].x;
                }
            }
            else
            {
                // todo
            }
        }
    }
    return 0;
}
