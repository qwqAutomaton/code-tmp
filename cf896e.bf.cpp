#include <bits/stdc++.h>
#define SZ 333                 //块的大小
#define L(a) ((a)*SZ - SZ + 1) //某个块左端点
#define R(a) ((a)*SZ)          //某个块右端点
using namespace std;
template <typename T>
inline void read(T &x)
{ //快读，这怎么能叫卡常呢（doge
    x = 0;
    char c = getchar(), f = 0;
    for (; c < '0' || c > '9'; c = getchar())
        if (c == '-')
            f = 1;
    for (; c >= '0' && c <= '9'; c = getchar())
        x = (x << 1) + (x << 3) + (c ^ 48);
    x = (f ? -x : x);
}
template <typename T>
inline void print(T x)
{
    if (x < 0)
        putchar('-'), x = -x;
    {
        if (x > 9)
            print(x / 10);
    }
    putchar(x % 10 + 48);
}
struct node
{
    int rt, nm;
} g[405][110005]; //每个块内值域结构体，rt是值域对应的祖先，num是这个值出现次数
int n, Q, bl[110005], fa[110005], v[110005], a[110005], mx[110005], lz[110005];
//bl是分块中的某个节点属于哪个块，a是初始的数组值，v是一个并查集节点对应的权值
//fa是并查集的祖先数组，mx是区间最大值，lz是懒标记
inline int getf(int x) { return x == fa[x] ? x : fa[x] = getf(fa[x]); }
//并查集找祖先，自带路径压缩（
inline void push(int x) //下压一个标记
{
    for (int i = L(x), e = R(x); i <= e; ++i)
        a[i] = v[getf(i)],
         g[x][a[i]].rt = g[x][a[i]].nm = 0, a[i] -= lz[x];
    //遍历这个块中的所有元素，把这个块的东西塞回a中
    lz[x] = 0;
    for (int i = L(x), e = R(x); i <= e; ++i)
        fa[i] = 0; //把这个区间清空
}
inline void init(int x) //初始化一个块
{
    mx[x] = 0;
    for (int i = L(x), e = R(x); i <= e; ++i)
    {
        mx[x] = max(mx[x], a[i]), ++g[x][a[i]].nm; //记录区间最大值以及某个值域位置元素个数
        if (g[x][a[i]].rt)
            fa[i] = g[x][a[i]].rt;
        else
            v[i] = a[i], g[x][a[i]].rt = fa[i] = i;
        //如果这个点已经有值域节点存在了，那就直接把当前节点合并到先前节点上去
        //否则新建一个值域节点
    }
}
inline void chng(int x, int a, int b) //把值域为a的位置和值域为b的合并
{
    node &s = g[x][a], &t = g[x][b]; //找到两个节点
    if (t.rt)
        fa[s.rt] = t.rt;
    else
        t.rt = s.rt, v[s.rt] = b;
    t.nm += s.nm, s.nm = s.rt = 0; //直接暴力合并，并把s给删除
                                   //如果b不存在就直接向a贺就好了，直接把a指向b
}
inline void atag(int x, int ad) //打标记
{
    if (ad <= mx[x] - lz[x] - ad)
    {
        for (int i = lz[x] + 1; i <= lz[x] + ad; ++i)
            if (g[x][i].rt)
                chng(x, i, i + ad);
        lz[x] += ad;
    }
    else
    {
        for (int i = mx[x]; i > lz[x] + ad; i--)
            if (g[x][i].rt)
                chng(x, i, i - ad);
        mx[x] = min(mx[x], lz[x] + ad);
    }
    //刚刚说的分两种情况讨论，应该还挺好懂的吧，不解释了
}
inline void chang(int l, int r, int x) //区间修改操作
{
    int p = bl[l], q = bl[r];
    push(p);
    if (p ^ q)
        push(q); //都先下推tag
    if (p ^ q)
    {
        for (int i = l, e = R(p); i <= e; ++i)
            if (a[i] > x)
                a[i] -= x;
        for (int i = L(q); i <= r; ++i)
            if (a[i] > x)
                a[i] -= x; //暴力的边块
        for (int i = p + 1; i <= q - 1; ++i)
            atag(i, x);   //整块打标记
        init(p), init(q); //再记录回去块的信息
    }
    else
    {
        for (int i = l; i <= r; ++i)
            if (a[i] > x)
                a[i] -= x;
        init(p);
    }
    //否则直接完全的暴力！
}
inline int query(int l, int r, int x) //区间查询操作
{
    //只需要对于每个块来查询值域上所对应的位置出现次数即可
    int p = bl[l], q = bl[r], res = 0; //分块基本套路，和chang差不多
    if (p ^ q)
    {
        for (int i = l, e = R(p); i <= e; ++i)
            if (v[getf(i)] - lz[p] == x)
                ++res;
        for (int i = L(q); i <= r; ++i)
            if (v[getf(i)] - lz[q] == x)
                ++res;
        for (int i = p + 1; i <= q - 1; i++)
            if (x + lz[i] <= 100000)
                res += g[i][x + lz[i]].nm; //防止越界
    }
    else
        for (int i = l; i <= r; ++i)
            if (v[getf(i)] - lz[p] == x)
                ++res;
    return res;
}
int main()
{
    freopen("in", "r", stdin);
    freopen("ans", "w",stdout);
    read(n), read(Q);
    for (int i = 1; i <= n; i++)
        read(a[i]), bl[i] = (i - 1) / SZ + 1;
    for (int i = bl[1]; i <= bl[n]; i++)
        init(i), lz[i] = 0;
    for (int f, l, r, x; Q--;)
    {
        read(f), read(l), read(r), read(x);
        if (f == 1)
            chang(l, r, x);
        else
            print(query(l, r, x)), putchar('\n');
    }
    return 0;
}