namespace SegmentTree
{
    const int MAXN = 100010;
    int a[MAXN]; // ађСа 
    struct node
    {
        int l, r;
        int sum;
        int lazy;
    } seg[MAXN << 2];
    inline void pushup(int cur)
    {
        seg[cur].sum = seg[cur << 1].sum + seg[cur << 1 | 1].sum;
    }
    inline void pushdown(int cur)
    {
        if (seg[cur].lazy)
        {
            seg[cur << 1].sum += seg[cur].lazy * (seg[cur << 1].r - seg[cur << 1].l + 1);
            seg[cur << 1 | 1].sum += seg[cur].lazy * (seg[cur << 1 | 1].r - seg[cur << 1 | 1].l + 1);
            seg[cur << 1].lazy += seg[cur].lazy;
            seg[cur << 1 | 1].lazy += seg[cur].lazy;
            seg[cur].lazy = 0;
        }
    }
    void build(int cur, int l, int r)
    {
        seg[cur].l = l;
        seg[cur].r = r;
        seg[cur].lazy = 0;
        if (l == r)
        {
            seg[cur].sum = a[l];
            return 0;
        }
        int mid = seg[cur].l + seg[cur].r >> 1;
        build(cur << 1, l, mid);
        build(cur << 1 | 1, mid + 1, r);
        pushup(cur);
    }
    void add(int cur, int l, int r, int v)
    {
        if (l <= seg[cur].l && seg[cur].r <= r)
        {
            seg[cur].lazy += v;
            seg[cur].sum += (seg[cur].r - seg[cur].l + 1) * v;
            return;
        }
        pushdown(cur);
        int mid = seg[cur].l + seg[cur].r >> 1;
        if (l <= mid)
            add(cur << 1, l, r, v);
        if (r > mid)
            add(cur << 1 | 1, l, r, v);
        pushup(cur);
    }
    int query(int cur, int l, int r)
    {
        if (l <= seg[cur].l && seg[cur].r <= r)
            return seg[cur].sum;
        pushdown(cur);
        int mid = seg[cur].l + seg[cur].r >> 1;
        int ans = 0;
        if (l <= mid)
            ans += query(cur << 1, l, r);
        if (r > mid)
            ans += query(cur << 1 | 1, l, r);
        pushup(cur);
        return ans;
    }
    void buildSegmentTree(int len, int *seq)
    {
        memcpy(a, seq, sizeof(int) * (len + 1));
        build(1, 1, len);
    }
    void addRange(int l, int r, int v)
    {
        add(1, l, r, v);
    }
    int queryRange(int l, int r)
    {
        query(1, l, r);
    }
}
using SegmentTree::buildSegmentTree;
using SegmentTree::addRange;
using SegmentTree::queryRange;

