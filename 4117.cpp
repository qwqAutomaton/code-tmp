#include <iostream>
#include <cstring>
#include <cmath>

const int MAXN = 100010;

int a[MAXN];

namespace dsu // 值相同的下标 merge 到一个集合里面（值为 x 则根为 pre[x]）
{
    int pre[MAXN], size[MAXN];
    int root(int x) { return x ^ pre[x] ? pre[x] = root(x) : x; }
    inline void build()
    {
        for (int i = 1; i <= 100001; i++)
        {
            pre[i] = i;
            size[i] = 1;
        }
    }
    inline void merge(int x, int y)
    {
        x = root(x), y = root(y);
        (x ^ y) && (pre[x] = y, size[y] += size[x]);
    }
}

namespace blocks
{
    int lpos, rpos, tag, max, blocklen; // tag: 块上减法标记; max: 块上最大值
    int blockdata[350];
    inline void buildblock(int n)
    {
        dsu::build();
        rpos = n * blocklen;
        lpos = (n - 1) * blocklen + 1;
        tag = 0;
        max = 100010;
        memcpy(a + lpos, blockdata, sizeof(int) * (rpos - lpos + 1));
    }
    inline void modify(int l, int r, int x)
    {
        // 散块修改：直接暴力重构
        if ((l ^ lpos) || (r ^ rpos))
        {
            for (int i = lpos; i <= rpos; i++)
                blockdata[i] -= tag;
        }
        // 整块修改：2x>max 时暴力把大于 x 的减去 x; 否则暴力把小于 x 的加上 x 然后 tag 加上 x
        // 注意 x 要减去 tag！
    }
}

inline int query(int val) { return dsu::size[val]; }

int main()
{
    return 0;
}