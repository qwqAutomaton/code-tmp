#pragma GCC optimize(2)
#include <iostream>
#include <string>
#include <tuple>
#include <set>
#include <iostream>

namespace DS
{
    template <typename T, size_t N = 1000010>
    class Splay
    {
        struct Node
        {
            int son[2], pre; // left son[0], right son[1], father
            int size;        // size of the subtree
            int cnt;         // value appear count
            T val;           // value of the node
            Node() : pre(0), size(0), cnt(0), val()
            {
                son[0] = 0;
                son[1] = 0;
            }
        } pool[N];
        int root, tot;
        int apply()
        {
            return ++tot;
        }
        void clear(int p)
        {
            pool[p] = Node();
        }
        void pushup(int p)
        {
            pool[p].size = pool[pool[p].son[0]].size + pool[pool[p].son[1]].size + pool[p].cnt;
        }
        int getSon(int p)
        {
            return pool[pool[p].pre].son[1] == p;
        }
        void rotate(int &p)
        {
            int q = pool[p].pre, r = pool[q].pre;
            int dir = getSon(p), dir2 = getSon(q);
            pool[q].son[dir] = pool[p].son[dir ^ 1];
            pool[pool[p].son[dir ^ 1]].pre = q;
            pool[p].son[dir ^ 1] = q;
            pool[q].pre = p;
            pool[p].pre = r;
            if (r)
                pool[r].son[dir2] = p;
            pushup(q);
            pushup(p);
        }
        void splay(int &p)
        {
            for (int pre; (pre = pool[p].pre); rotate(p))
                if (pool[pre].pre)
                    rotate(getSon(pre) == getSon(p) ? pre : p);
            root = p;
        }
        void printMidseq(int cur)
        {
            if (!cur)
                return;
            printMidseq(pool[cur].son[0]);
            for (int i = 1; i <= pool[cur].cnt; i++)
                std::cout << pool[cur].val << ' ';
            printMidseq(pool[cur].son[1]);
        }
        int pre()
        {
            int cur = pool[root].son[0];
            while (pool[cur].son[1])
                cur = pool[cur].son[1];
            splay(cur);
            return cur;
        }
        int nxt()
        {
            int cur = pool[root].son[1];
            while (pool[cur].son[0])
                cur = pool[cur].son[0];
            splay(cur);
            return cur;
        }

    public:
        Splay() : root(0), tot(0) {}
        void print() { printMidseq(root); }
        void insert(T val)
        {
            if (!root)
            {
                int cur = apply();
                pool[cur].val = val;
                pool[cur].cnt = 1;
                root = cur;
                pushup(cur);
                return;
            }
            int cur = root, pre = pool[root].pre;
            while (true)
            {
                if (pool[cur].val == val)
                {
                    pool[cur].cnt++;
                    pushup(cur);
                    pushup(pre);
                    splay(cur);
                    return;
                }
                pre = cur;
                cur = pool[cur].son[pool[cur].val < val];
                if (!cur)
                {
                    cur = apply();
                    pool[cur].pre = pre;
                    pool[cur].val = val;
                    pool[cur].cnt = 1;
                    pool[pre].son[pool[pre].val < val] = cur;
                    pushup(cur);
                    pushup(pre);
                    splay(cur);
                    return;
                }
            }
        }
        int queryRank(T val)
        {
            if (!root)
                return -1;
            int cur = root, rank = 0;
            while (1)
            {
                if (!cur)
                    return -1;
                if (val < pool[cur].val)
                    cur = pool[cur].son[0];
                else
                {
                    rank += pool[pool[cur].son[0]].size;
                    if (val == pool[cur].val)
                    {
                        splay(cur);
                        return rank + 1;
                    }
                    rank += pool[cur].cnt;
                    cur = pool[cur].son[1];
                }
            }
        }
        T queryVal(int rank)
        {
            if (!root)
                return T();
            int cur = root, pre = pool[cur].pre;
            while (1)
            {
                if (!cur)
                    return T();
                if (pool[cur].son[0] && rank <= pool[pool[cur].son[0]].size)
                    cur = pool[cur].son[0];
                else
                {
                    rank -= pool[pool[cur].son[0]].size;
                    rank -= pool[cur].cnt;
                    if (rank <= 0)
                    {
                        splay(cur);
                        return pool[cur].val;
                    }
                    cur = pool[cur].son[1];
                }
            }
        }
        T prev(T val)
        {
            insert(val);
            T ret = pool[pre()].val;
            remove(val);
            return ret;
        }
        T next(T val)
        {
            insert(val);
            T ret = pool[nxt()].val;
            remove(val);
            return ret;
        }
        void remove(T val)
        {
            queryRank(val);
            if (pool[root].cnt > 1)
            {
                pool[root].cnt--;
                pushup(root);
                return;
            }
            if (!pool[root].son[0] && !pool[root].son[1])
            {
                // clear(root);
                root = 0;
                return;
            }
            if (!pool[root].son[0])
            {
                int cur = root;
                root = pool[cur].son[1];
                pool[root].pre = 0;
                // clear(cur);
                return;
            }
            if (!pool[root].son[1])
            {
                int cur = root;
                root = pool[cur].son[0];
                pool[root].pre = 0;
                // clear(cur);
                return;
            }
            int cur = root;
            int x = pre();
            pool[pool[cur].son[1]].pre = x;
            pool[x].son[1] = pool[cur].son[1];
            // clear(cur);
            pushup(root);
        }
        int max()
        {
            int cur = root;
            while (pool[cur].son[1])
                cur = pool[cur].son[1];
            return pool[cur].val;
        }
    };
}
class SplitSet
{
private:
    using tpl = std::tuple<int, int, int>;
    struct node
    {
        int l, r;
        bool operator<(const node &n) const { return l < n.l; }
        node(int l = 0, int r = 0) : l(l), r(r) {}
    };
    std::set<node> s;

public:
    SplitSet()
    {
        s.clear();
    }
    tpl split(int pos)
    {
        auto it = s.lower_bound(node(pos));
        if (it->l == pos && it != s.end())
            return tpl(-1, -1, -1);
        it--;
        int l = it->l, r = it->r;
        s.erase(it);
        it = s.insert(node(l, pos)).first;
        s.insert(it, node(pos, r));
        return tpl(r - l, pos - l, r - pos);
    }
    void set_size(int n)
    {
        s.insert(node(0, n));
    }
} line, row;
DS::Splay<int> quq, qnq; // line, row
int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);
    int n, m, k, lmax, rmax;
    std::cin >> n >> m >> k;
    line.set_size(m);
    row.set_size(n);
    quq.insert(m);
    qnq.insert(n);
    lmax = m;
    rmax = n;
    for (int i = 1, val; i <= k; i++)
    {
        std::string opt;
        std::cin >> opt >> val;
        if (opt == "line")
        {
            int ori, cr1, cr2;
            std::tie(ori, cr1, cr2) = line.split(val);
            if (ori != -1)
            {
                quq.remove(ori);
                quq.insert(cr1);
                quq.insert(cr2);
                lmax = quq.max();
            }
        }
        else if (opt == "row")
        {
            int ori, cr1, cr2;
            std::tie(ori, cr1, cr2) = row.split(val);
            if (ori != -1)
            {
                qnq.remove(ori);
                qnq.insert(cr1);
                qnq.insert(cr2);
                rmax = qnq.max();
            }
        }
        std::cout << lmax * 1LL * rmax << '\n';
    }
    return 0;
}