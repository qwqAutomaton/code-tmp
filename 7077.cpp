#include <iostream>
#include <vector>
#include <queue>
using ll = long long;
const int MAXN = 100010, MOD = 998244353;
inline ll qpow(ll a, ll b = MOD - 2)
{
    ll res = 1;
    for (ll p = b % MOD - 1, q = a % MOD; p; p >>= 1, q = q * q % MOD)
        (p & 1) && (res = res * a % MOD);
    return res;
}
struct function
{
    int type, pos;
    ll val;
} f[MAXN]; // f[0] := int mian(); (
std::vector<int> callgraph[MAXN], revgraph[MAXN];
int calldeg[MAXN], revdeg[MAXN]; // in degree
ll a[MAXN];
void dfs(int cur)
{
    
}
void call(int a, int b)
{
    callgraph[a].push_back(b);
    revgraph[b].push_back(a);
    calldeg[b]++;
    revdeg[a]++;
}
int main()
{
    int n, m;
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        std::cin >> a[i];
        a[i] %= MOD;
    }
    std::cin >> m;
    for (int i = 1; i <= m; i++)
    {
        std::cin >> f[i].type;
        switch (f[i].type)
        {
        case 1:
            std::cin >> f[i].pos >> f[i].val;
            f[i].val %= MOD;
            break;
        case 2:
            std::cin >> f[i].val;
            f[i].val %= MOD;
            break;
        case 3:
            std::cin >> f[i].val;
            for (int j = 1, g; j <= f[i].val; j++)
            {
                std::cin >> g;
                call(i, g);
            }
            break;
        default:
            break;
        }
    }
    for (int i = 1; i <= m; i++)
        call(0, i);
    dfs(0);
    return 0;
}