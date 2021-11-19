#include <iostream>
#include <cstring>
#include <vector>
#include <stack>
std::vector<int> to[10010], to2[10010];
int dfn[10010], low[10010], v[10010], instack[10010], dfntot = 0;
std::stack<int> st;
int scc[10010], scctot = 0, size[10010];
void tarjan(int cur)
{
    instack[cur] = dfn[cur] = low[cur] = ++dfntot;
    st.push(cur);
    for (auto i : to[cur])
    {
        if (!dfn[i])
        {
            tarjan(i);
            low[cur] = std::min(low[cur], low[i]);
        }
        else if (instack[i])
            low[cur] = std::min(low[cur], dfn[i]);
    }
    if (dfn[cur] == low[cur])
    {
        scctot++;
        size[scctot] = 0;
        while (st.top() != cur)
        {
            scc[st.top()] = scctot;
            size[scctot] += v[st.top()];
            instack[st.top()] = 0;
            st.pop();
        }
        scc[st.top()] = scctot;
        size[scctot] += v[st.top()];
        instack[st.top()] = 0;
        st.pop();
    }
}
int f[10010];
int dp(int p)
{
    if (~f[p])
        return f[p];
    f[p] = size[p];
    int maxval = 0;
    for (auto i : to2[p])
        maxval = std::max(maxval, dp(i));
    return f[p] += maxval;
}
int main()
{
    memset(f, -1, sizeof(f));
    int n, m;
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++)
        std::cin >> v[i];
    for (int i = 1, u, v; i <= m; i++)
    {
        std::cin >> u >> v;
        to[u].push_back(v);
    }
    for (int i = 1; i <= n; i++)
        if (!dfn[i])
            tarjan(i);
    for (int i = 1; i <= n; i++)
        for (auto j : to[i])
            if (scc[i] != scc[j])
                to2[scc[i]].push_back(scc[j]);
    // for (int i = 1; i <= scctot; i++)
    // std::cout << size[i] << std::endl;
    int maxv = -1;
    for (int i = 1; i <= n; i++)
        maxv = std::max(maxv, dp(i));
    std::cout << maxv << std::endl;
    return 0;
}