#include <iostream>
#include <cstring>
#include <set>
int m, tot = 0;
int head[50010], next[100010], to[100010], dis[100010], etot = 1;
int dfs(int cur, int k, int pre = -1)
{
    std::multiset<int> multiset;
    multiset.clear();
    for (int i = head[cur]; i; i = next[i])
    {
        if (to[i] == pre)
            continue;
        int val = dfs(to[i], k, cur) + dis[i];
        if (val >= k)
            tot++;
        else
            multiset.insert(val);
    }
    int maxval = -1;
    while (!multiset.empty())
    {
        if (multiset.size() == 1)
            return std::max(maxval, *multiset.begin());
        auto it = multiset.lower_bound(k - *multiset.begin());
        if (it == multiset.begin() && multiset.count(*it) == 1)
            it++;
        if (it == multiset.end())
        {
            maxval = std::max(maxval, *multiset.begin());
            multiset.erase(multiset.find(*multiset.begin()));
        }
        else
        {
            tot++;
            multiset.erase(multiset.find(*it));
            multiset.erase(multiset.find(*multiset.begin()));
        }
    }
    return std::max(0, maxval);
}
inline void add(int u, int v, int d)
{
    to[++etot] = v;
    dis[etot] = d;
    next[etot] = head[u];
    head[u] = etot;
}
bool check(int k)
{
    tot = 0;
    dfs(1, k);
    return tot >= m;
}
int main()
{
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
    int n, l = 0, r = 0;
    std::cin >> n >> m;
    for (int i = 1, u, v, d; i < n; i++)
    {
        std::cin >> u >> v >> d;
        add(u, v, d);
        add(v, u, d);
        r += d;
    }
    while (l < r)
    {
        int mid = l + r + 1 >> 1;
        if (check(mid))
            l = mid;
        else
            r = mid - 1;
    }
    std::cout << l;
    return 0;
}