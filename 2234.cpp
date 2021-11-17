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
                int size, cnt;
                T val;
                Node() : pre(0), size(0), cnt(0), val() { son[0] = son[1] = 0; }
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
                node[p].size = node[node[p].son[0]].size + node[node[p].son[1]].size + node[p].cnt;
            }
            void rotate(int &p)
            {
                int q = node[p].pre;
                int r = node[q].pre;
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
                    if (node[pre].pre)
                        rotate(getSon(pre) == getSon(p) ? pre : p);
                root = p;
            }
            int find(T val)
            {
                if (!root)
                    return 0;
                int cur = root;
                while (1)
                {
                    if (!cur)
                        return 0;
                    if (node[cur].val == val)
                        return cur;
                    cur = node[cur].son[node[cur].val < val];
                }
            }
            int rootNext()
            {
                if (node[root].cnt > 1)
                    return root;
                int cur = node[root].son[1];
                while (node[cur].son[0])
                    cur = node[cur].son[0];
                splay(cur);
                return root;
            }
            int rootPrev()
            {
                if (node[root].cnt > 1)
                    return root;
                int cur = node[root].son[0];
                while (node[cur].son[1])
                    cur = node[cur].son[1];
                splay(cur);
                return root;
            }
            int unsafe_getRank(T val)
            {
                int rank = 0, cur = root;
                while (1)
                {
                    if (val < node[cur].val)
                        cur = node[cur].son[0];
                    else
                    {
                        rank += node[node[cur].son[0]].size;
                        if (val == node[cur].val)
                        {
                            splay(cur);
                            return rank + 1;
                        }
                        rank += node[cur].cnt;
                    }
                }
            }

        public:
            Splay() : root(0), tot(0){};
            void insert(T val)
            {
                if (!root)
                {
                    root = apply();
                    node[root].val = val;
                    node[root].cnt = 1;
                    pushup(root);
                    return;
                }
                int cur = root, pre = node[cur].pre;
                while (true)
                {
                    if (node[cur].val == val)
                    {
                        node[cur].cnt++;
                        pushup(cur);
                        splay(cur);
                        return;
                    }
                    pre = cur;
                    cur = node[cur].son[node[cur].val < val];
                    if (!cur)
                    {
                        cur = apply();
                        node[pre].son[node[pre].val < val] = cur;
                        node[cur].cnt = 1;
                        node[cur].val = val;
                        node[cur].pre = pre;
                        pushup(cur);
                        pushup(pre);
                        splay(cur);
                        return;
                    }
                }
            }
            void remove(T val)
            {
                int cur = find(val);
                if (!cur)
                    return;
                splay(cur);
                cur = root;
                if (node[cur].cnt > 1)
                {
                    node[cur].cnt--;
                    pushup(cur);
                    return;
                }
                if (!node[cur].son[0] && !node[cur].son[1])
                {
                    root = 0;
                    tot = 0;
                    return;
                }
                if (!node[cur].son[1])
                {
                    cur = node[cur].son[0];
                    node[cur].pre = 0;
                    root = cur;
                    return;
                }
                if (!node[cur].son[0])
                {
                    cur = node[cur].son[1];
                    node[cur].pre = 0;
                    root = cur;
                    return;
                }
                if (node[node[cur].son[0]].size < node[node[cur].son[1]].size)
                {
                    int x = rootNext();
                    node[node[cur].son[0]].pre = x;
                    node[x].son[0] = node[cur].son[0];
                    pushup(root);
                    return;
                }
                else
                {
                    int x = rootPrev();
                    node[node[cur].son[1]].pre = x;
                    node[x].son[1] = node[cur].son[1];
                    pushup(root);
                    return;
                }
            }
            T prev(T val)
            {
                insert(val);
                rootPrev();
                T res = node[root].val;
                remove(val);
                return res;
            }
            T next(T val)
            {
                insert(val);
                rootNext();
                T res = node[root].val;
                remove(val);
                return res;
            }
            int getRank(T val)
            {
                insert(val);
                int rank = unsafe_getRank(val);
                remove(val);
                return rank;
            }
            T getVal(int rank)
            {
                int cur = root;
                while (1)
                {
                    if (!cur)
                        return T();
                    if (node[cur].son[0] && node[node[cur].son[0]].size >= rank)
                        cur = node[cur].son[0];
                    else
                    {
                        rank -= node[node[cur].son[0]].size + node[cur].cnt;
                        if (rank <= 0)
                        {
                            splay(cur);
                            return node[root].val;
                        }
                        cur = node[cur].son[1];
                    }
                }
            }
        };
    }
}
#include <iostream>
DS::BalancedTree::Splay<long long, 1000010> splay;
int main()
{
    splay.insert(2147483647);
    splay.insert(-2147483648);
    int n;
    std::cin >> n;
    int ans = 0;
    int val;
    std::cin >> val;
    ans += val;
    if (n == 1)
    {
        std::cout << ans << std::endl;
        return 0;
    }
    splay.insert(val);
    for (int i = 2; i <= n; i++)
    {
        std::cin >> val;
        long long p = splay.prev(val), q = splay.next(val);
        splay.insert(val);
        ans += std::min(val - p, q - val);
    }
    std::cout << ans;
    return 0;
}