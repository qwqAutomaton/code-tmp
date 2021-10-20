#include <iostream>
#include <vector>
#include <queue>
const int MOD = 998244353;
const int MAXN = 100010;
using ll = long long;
inline ll qpow(ll a, ll b = MOD - 2)
{
    b %= MOD - 1;
    ll ans = 1;
    for (; b; b >>= 1, a = a * a % MOD)
        (b & 1) && (ans = ans * a % MOD);
    return ans;
}
struct func
{
    int type;
    ll p, v;
} f[MAXN];
int calldeg[MAXN], invdeg[MAXN];
ll a[MAXN], callcnt[MAXN];
ll addval[MAXN];
std::vector<int> callgraph[MAXN], invgraph[MAXN];
ll mul[MAXN];
bool vis[MAXN];
void dfs(int cur)
{
    if (vis[cur])
        return;
    vis[cur] = 1;
    for (auto i : callgraph[cur])
    {
        dfs(i);
        (mul[cur] *= mul[i]) %= MOD;
    }
}
void topo(int n)
{
    std::queue<int> que;
    for (int i = 1; i <= n; i++)
        if (!calldeg[i])
            que.push(i);
    while (!que.empty())
    {
        
    }
}
int main()
{
    int n, m;
    std::cin >> n;
    for (int i = 1; i <= n; i++)
        std::cin >> a[i];
    std::cin >> m;
    for (int i = 1; i <= m; i++)
    {
        mul[i] = 1;
        std::cin >> f[i].type;
        switch (f[i].type)
        {
        case 1:
            std::cin >> f[i].p >> f[i].v;
            f[i].v %= MOD;
            callcnt[i]++;
            break;
        case 2:
            std::cin >> f[i].v;
            f[i].v %= MOD;
            mul[i] = f[i].v;
            break;
        case 3:
            std::cin >> k;
            callcnt[i]++;
            for (int j = 1, qwq; j <= k; j++)
            {
                std::cin >> qwq;
                callgraph[qwq].push_back(i);
                invgraph[i].push_back(qwq);
                calldeg[qwq]++;
                invdeg[i]++;
            }
            break;
        default:
            std::cerr << "qwq" << std::endl;
            return -1;
            break;
        }
    }
    for (int i = 1; i <= m; i++)
        if (!invdeg[i])
            dfs(i);
    topo(m);
    return 0;
}

