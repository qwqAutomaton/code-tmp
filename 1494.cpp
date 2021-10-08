#include <iostream>

int blocklen, n, m;

struct Query
{
    int l, r;
    bool operator<(const Query &a)
    {
        if (l / maxn ^ a.l / maxn)
            return l < x.l;
        return r < a.r;
    }
}

