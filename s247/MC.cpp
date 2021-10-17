#include <iostream>
#include <stack>
#include <map>
#define int long long
const int MAXN = 1000005, MOD = 19260817, MAXM = 2000005;
struct edge
{
    int from, to;
    bool tag;
} e[MAXN];
struct Query
{
    int op;
    union
    {
        struct { int x, t, y; } op1;
        struct { int s, flag; } op2;
        struct { int x, n, y; } op3;
    } args;
} qry[MAXN];
std::stack<int> ans;
int fac[MAXM], inv[MAXM];
int sum[MAXN], pre[MAXN], size[MAXN];
std::map<int, int> cnt[MAXN];
int n, m, q, tot = 0;
int root(int x) { return x ^ pre[x] ? (pre[x] = root(pre[x])) : x; }
inline void merge(int x, int y)
{
    x = root(x);
    y = root(y);
    if (x == y)
        return;
    if (size[x] < size[y])
        std::swap(x, y);
    for (auto i : cnt[y])
        cnt[x][i.first] += i.second;
    size[x] += size[y];
    sum[x] += sum[y];
    pre[y] = x;
}
inline void add_edge(int u, int v)
{
    e[++tot].from = u;
    e[tot].to = v;
    e[tot].tag = false;
}
inline int qpow(int a, int b = MOD - 2)
{
    int res = 1;
    while (b)
    {
        if (b & 1)
            res = res * 1LL * a % MOD;
        a = a * 1LL * a % MOD;
        b >>= 1;
    }
    return res % MOD;
}
inline void preproc()
{
    int M = MAXM - 5;
    fac[1] = 1;
    for (int i = 2; i <= M; i++)
        fac[i] = fac[i - 1] * 1LL * i % MOD;
    inv[M] = qpow(fac[M]);
    for (int i = M - 1; i >= 0; i--)
        inv[i] = inv[i + 1] * 1LL * (i + 1) % MOD;
}
inline int C(int n, int m)
{
    return n < m ? 0 : 1LL * fac[n] * inv[m] % MOD * inv[n - m] % MOD;
}
signed main()
{
    std::ios::sync_with_stdio(false);
    preproc();
    std::cin >> n >> m >> q;
    for (int i = 1, t, y; i <= n; i++)
    {
        pre[i] = i;
        size[i] = 1;
        std::cin >> t >> y;
        cnt[i][y] += t;
        sum[i] += t;
    }
    for (int i = 1, u, v; i <= m; i++)
    {
        std::cin >> u >> v;
        add_edge(u, v);
    }
    for (int i = 1; i <= q; i++)
    {
        std::cin >> qry[i].op;
        switch (qry[i].op)
        {
        case 1:
            std::cin >> qry[i].args.op1.x >> qry[i].args.op1.t >> qry[i].args.op1.y;
            cnt[qry[i].args.op1.x][qry[i].args.op1.y] += qry[i].args.op1.t;
            sum[qry[i].args.op1.x] += qry[i].args.op1.t;
            break;
        case 2:
            std::cin >> qry[i].args.op2.s;
            if (!e[qry[i].args.op2.s].tag)
            {
                e[qry[i].args.op2.s].tag = true;
                qry[i].args.op2.flag = true;
            }
            else
                qry[i].args.op2.flag = false;
            break;
        case 3:
            std::cin >> qry[i].args.op3.x >> qry[i].args.op3.n >> qry[i].args.op3.y;
            break;
        default:
            std::cerr << "\033[31mFuck CCF!\033[0m\n";
            return -1;
            break;
        }
    }
    for (int i = 1; i <= m; i++)
        if (!e[i].tag)
            merge(e[i].from, e[i].to);
    for (int u; q; q--, u = 0)
        switch (qry[q].op)
        {
        case 1:
            u = root(qry[q].args.op1.x);
            cnt[u][qry[q].args.op1.y] -= qry[q].args.op1.t;
            sum[u] -= qry[q].args.op1.t;
            break;
        case 2:
            if (qry[q].args.op2.flag)
                merge(e[qry[q].args.op2.s].from, e[qry[q].args.op2.s].to);
            break;
        case 3:
            u = root(qry[q].args.op3.x);
            ans.push(1LL * C(cnt[u][qry[q].args.op3.y], qry[q].args.op3.n) * qpow(C(sum[u], qry[q].args.op3.n)) % MOD);
            break;
        default:
            std::cerr << "\033[31mFuck CCF!\033[0m\n";
            return -1;
            break;
        }
    while (!ans.empty())
    {
        std::cout << ans.top() << '\n';
        ans.pop();
    }
    return 0;
}

