#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <set>
#define iter std::set<node>::iterator
namespace IO
{
    inline void read(int &x)
    {
        x = 0;
        char chr = getchar();
        while (!isdigit(chr))
            chr = getchar();
        while (isdigit(chr))
            x = x * 10 + (chr & 15), chr = getchar();
    }
    inline void read(long long &x)
    {
        x = 0;
        char chr = getchar();
        while (!isdigit(chr))
            chr = getchar();
        while (isdigit(chr))
            x = x * 10 + (chr & 15), chr = getchar();
    }
    inline void writeln(int &x)
    {
        printf("%d\n", x);
    }
    inline void writeln(long long &x)
    {
        printf("%lld\n", x);
    }
}
namespace Datagen
{
    long long seed, vmax;
    inline void init()
    {
        IO::read(seed);
        IO::read(vmax);
    }
    inline int rand()
    {
        int ret = seed;
        seed = (seed * 7LL + 13) % 1000000007;
        return ret;
    }
    inline int genmod(int mod = vmax) { return rand() % mod; }
}
struct node
{
    int l, r;
    mutable long long v;
    node(int l = 0, int r = 0, long long v = 0) : l(l), r(r), v(v) {}
    bool operator<(const node &n) const { return l < n.l; }
};
std::set<node> s;
std::vector<node> tmp;
inline iter split(int pos)
{
    iter it = s.lower_bound(node(pos));
    if (it != s.end() && it->l == pos)
        return it;
    it--;
    node tmp = *it;
    s.erase(it);
    s.insert(node(tmp.l, pos - 1, tmp.v));
    return s.insert(node(pos, tmp.r, tmp.v)).first;
}
inline int qpow(long long a, int p, int mod)
{
    long long res = 1;
    a %= mod;
    while (p)
    {
        if (p & 1)
            (res *= a) %= mod;
        (a *= a) %= mod;
        p >>= 1;
    }
    return res;
}
int main()
{
    int n, m;
    IO::read(n);
    IO::read(m);
    Datagen::init();
    for (int i = 1; i <= n; i++)
        s.emplace(i, i, Datagen::genmod() + 1);
    for (int i = 1; i <= m; i++)
    {
        int op = Datagen::genmod(4) + 1, l = Datagen::genmod(n) + 1, r = Datagen::genmod(n) + 1;
        int x, y;
        (l > r) && (std::swap(l, r), true);
        if (op == 3)
            x = Datagen::genmod(r - l + 1) + 1;
        else
            x = Datagen::genmod() + 1;
        if (op == 4)
            y = Datagen::genmod() + 1;
        iter rit = split(r + 1);
        switch (op)
        {
        case 1:
            for (iter lit = split(l); lit != rit; lit++)
                lit->v += x;
            break;
        case 2:
            s.erase(split(l), rit);
            s.insert(node(l, r, x));
            break;
        case 3:
        {
            for (iter lit = split(l); lit != rit; lit++)
                tmp.push_back(*lit);
            std::sort(tmp.begin(), tmp.end());
            for (std::vector<node>::iterator it = tmp.begin(); it != tmp.end(); it++)
                if (x -= (it->r - it->l + 1) <= 0)
                {
                    IO::writeln(it->v);
                    break;
                }
            tmp.clear();
            break;
        }
        case 4:
        {
            long long res = 0;
            for (iter lit = split(l); lit != rit; lit++)
                (res += (lit->r - lit->l + 1) * qpow(lit->v, x, y) % y) %= y;
            IO::writeln(res);
            break;
        }
        default:
            std::cerr << "DLLXL!" << std::endl;
            return -1;
            break;
        }
    }
    return 0;
}