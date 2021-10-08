
namespace treap
{
template<class T>
struct node
{
    T val;
    int l, r;
    int rnd;
    int cnt, size;
};
int rand()
{
    static int _QwQ_ = 998244353;
    return _QwQ_ = (1LL * _QwQ_ * 998244383 + 13331) % 2147483647;
}
template<class T, unsigned size>
class Treap
{
private:
    node<T> tr[size];
    int tail, root;
    inline void pushup(int cur) { tr[cur].size = tr[cur].cnt + tr[tr[cur].son[0]].size + tr[tr[cur].son[1]].size; }
    inline void lrotate(int &p)
    {
        int t = tr[p].r;
        tr[p].r = tr[t].l;
        tr[t].l = p;
        pushup(p);
        p = t;
        pushup(p);
    }
    inline void rrotate(int &p)
    {
        int t = tr[p].l;
        tr[p].l = tr[t].r;
        tr[t].r = p;
        pushup(p);
        p = t;
        pushup(p);
    }
    void _insert(T val, int &cur)
    {
        if (!cur)
        {
            cur = ++tail;
            tr[cur].size = tr[cur].cnt = 1;
            tr[cur].l = tr[cur].r = 0;
            tr[cur].val = val;
            tr[cur].rnd = rand();
            return;
        }
        tr[cur].size++;
        if (tr[cur].val == val)
        {
            tr[cur].cnt++;
        }
        else if (tr[cur].val < val)
        {
            _insert(val, tr[cur].r);
            if (tr[cur].rnd < tr[tr[cur].r].rnd)
                lrotate(cur);
        }
        else
        {
            _insert(val, tr[cur].l);
            if (tr[cur].rnd < tr[tr[cur].l].rnd)
                rrotate(cur);
        }
    }
    bool _remove(T val,int &cur)
    {
        if (!cur)
            return false;
        if (tr[cur].val == val)
        {
            if (tr[cur].cnt > 1)
            {
                tr[cur].cnt--;
                tr[cur].size--;
                return true;
            }
            else
            {
                if (tr[tr[cur].l].rnk < tr[tr[cur].r].rnk)
                    lrotate(cur);
                else
                    rrotate(cur);
                return _remove(val, cur);
            }
        }
        bool f;
        if (tr[cur].val < x)
            f = _remove(x, tr[cur].r);
        else
            f = _remove(x, tr[cur].l);
        if (f)
            tr[cur].size--;
        return f;
    }

public:
    Treap(): tail(0), root(0) {}
    inline insert(int val) { _insert(val, root); }
    inline bool remove(int val) { return _remove(val, root); }

};
} // namespace treap

