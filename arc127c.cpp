#include <iostream>
#include <set>
const int MAXN = 100010;
struct node
{
    int l, r;
    mutable bool val;
    bool operator<(const node &n) const { return l < n.l; }
    node(int l = 0, int r = 0, bool val = false)
        : l(l), r(r), val(val) {}
};
std::set<node> s;
auto split(int pos)
{
    auto i = s.lower_bound(node(pos));
    if (i != s.end() && i->l == pos)
        return i;
    i--;
    int l = i->l, r = i->r;
    bool val = i->val;
    s.erase(i);
    s.insert(node(l, pos - 1, val));
    return s.insert(node(pos, r, val)).first;
}
inline void assign(int l, int r)
{
    auto itr = split(r + 1);
    s.erase(split(l), itr);
    s.insert(node(l, r, false));
}
int main()
{
    int n, m;
    std::cin >> n >> m;
    s.insert(node(1, n, true));
    for (int i = 1, l, r; i <= m; i++)
    {
        std::cin >> l >> r;
        assign(1, l - 1);
        assign(r + 1, n);
    }
    int ans = 0;
    for (auto it = s.begin(); it != s.end(); it++)
        ans += (it->r - it->l + 1) * it->val;
    std::cout << ans << std::endl;
    return 0;
}

