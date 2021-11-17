#include <iostream>
namespace DS
{
    namespace BalancedTree
    {
        template <typename T = int, unsigned N = 1000010>
        class Splay
        {
        private:
            struct Node
            {
                int son[2], pre;
                int size, cnt, tag;
                T val;
                Node() : pre(0), size(0), cnt(0), tag(0), val() { son[0] = son[1] = 0; }
            };
            Node node[N];
            int root, tot;
            int apply()
            {
                node[++tot] = Node();
                return tot;
            }
            int getSon(int p) { return node[node[p].pre].son[1] == p; }
            void pushup(int p)
            {
                if (p)
                    node[p].size = node[node[p].son[0]].size + node[node[p].son[1]].size + node[p].cnt;
            }
            void pushdown(int p)
            {
                if (p && node[p].tag)
                {
                    node[p].tag ^= 1;
                    node[node[p].son[0]].tag ^= 1;
                    node[node[p].son[1]].tag ^= 1;
                    std::swap(node[p].son[0], node[p].son[1]);
                }
            }
            void rotate(int &p)
            {
                int q = node[p].pre;
                int r = node[q].pre;
                pushdown(p);
                pushdown(q);
                int dir = getSon(p), dir2 = getSon(q);
                node[q].son[dir] = node[p].son[dir ^ 1];
                if (node[q].son[dir])
                    node[node[q].son[dir]].pre = q;
                node[p].son[dir ^ 1] = q;
                node[q].pre = p;
                node[p].pre = r;
                if (r)
                    node[r].son[dir2] = p;
                pushup(q);
                pushup(p);
            }
            void splay(int p, int limpre = 0)
            {
                for (int pre; (pre = node[p].pre) != limpre; rotate(p))
                    if (node[pre].pre != limpre)
                        rotate(getSon(pre) == getSon(p) ? pre : p);
                if (!limpre)
                    root = p;
            }
            int find(int rank)
            {
                int cur = root;
                while (1)
                {
                    if (!cur)
                    {
                        throw "FUCKCCF";
                        return 0;
                    }
                    pushdown(cur);
                    if (rank <= node[node[cur].son[0]].size)
                        cur = node[cur].son[0];
                    else
                    {
                        rank -= node[node[cur].son[0]].size + node[cur].cnt;
                        if (rank <= 0)
                            return cur;
                        cur = node[cur].son[1];
                    }
                }
            }
            int build(T *arr, int l, int r, int pre)
            {
                if (l > r)
                    return 0;
                int mid = (l + r) >> 1;
                int ret = apply();
                node[ret].val = arr[mid];
                node[ret].pre = pre;
                node[ret].cnt = 1;
                node[ret].son[0] = build(arr, l, mid - 1, ret);
                node[ret].son[1] = build(arr, mid + 1, r, ret);
                pushup(ret);
                return ret;
            }
            void printMidseq(int cur)
            {
                if (!cur)
                    return;
                pushdown(cur);
                printMidseq(node[cur].son[0]);
                if (node[cur].val != -2147483648 && node[cur].val != 2147483647)
                    std::cout << node[cur].val << ' ';
                printMidseq(node[cur].son[1]);
            }

        public:
            Splay() : root(0), tot(0){};
            void build(T *arr, int len)
            {
                root = build(arr, 1, len, 0);
            }
            void print()
            {
                printMidseq(root);
                std::cout << std::endl;
            }
            void reverse(int l, int r)
            {
                int pref = find(l - 1);
                int suff = find(r + 1);
                splay(pref);
                splay(suff, pref);
                node[node[node[root].son[1]].son[0]].tag ^= 1;
            }
        };
    }
}
DS::BalancedTree::Splay<int, 1000010> splay;
int a[1000010];
int main()
{
    int n, q;
    std::cin >> n >> q;
    a[1] = -2147483648;
    for (int i = 1; i <= n; i++)
        a[i + 1] = i;
    a[n + 2] = 2147483647;
    splay.build(a, n + 2);
    for (int i = 1, l, r; i <= q; i++)
    {
        std::cin >> l >> r;
        splay.reverse(l + 1, r + 1);
    }
    splay.print();
    return 0;
}