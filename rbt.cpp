#include <iostream>
#include <cstring>
#include <algorithm>
namespace DS
{
    namespace BalancedTree
    {
        using T = int;
        const unsigned N = 1000010;
        // template <typename T, unsigned N = 1000010>
        class RBTree
        {
        private:
#define BLACK 0
#define RED 1
            int pre[N], son[N][2], size[N], cnt[N], colour[N];
            T val[N];
            int root, tot;
            void change(int p)
            {
                colour[p] ^= 1;
            }
            void push_up(int p)
            {
                size[p] = cnt[p];
                if (son[p][0])
                    size[p] += size[son[p][0]];
                if (son[p][1])
                    size[p] += size[son[p][1]];
            }
            int get_son(int p)
            {
                return son[pre[p]][1] == p;
            }
            void rotate(int p)
            {
                if (root == p)
                    return;
                int q = pre[p], r = pre[q];
                int dir = get_son(p), dir2 = get_son(q);
                son[q][dir] = son[p][dir ^ 1];
                if (son[q][dir])
                    pre[son[q][dir]] = q;
                son[p][dir ^ 1] = q;
                pre[q] = p;
                pre[p] = r;
                if (r)
                    son[r][dir2] = p;
                else
                    root = p;
                push_up(q);
                push_up(p);
            }
            void maintain_insert(int p)
            {
                while (true)
                {
                    if (p == root)
                    {
                        colour[p] = BLACK;
                        return;
                    }
                    if (colour[pre[p]] == BLACK)
                        return;
                    int uncle = son[pre[pre[p]]][get_son(pre[p]) ^ 1];
                    // Case 1: R-R-B-R
                    if (uncle && colour[uncle] == RED)
                    {
                        change(pre[p]), change(pre[pre[p]]), change(uncle);
                        p = pre[pre[p]];
                    }
                    // Case 2: R-R-B-B
                    else
                    {
                        /*
                        Case 2.1:
                          B
                         R B
                        R
                        */
                        if (get_son(p) == get_son(pre[p]))
                        {
                            change(uncle), change(pre[p]), change(pre[pre[p]]);
                            rotate(pre[p]);
                        }
                        /*
                        Case 2.2:
                           B
                         R   R
                          R
                        */
                        else
                        {
                            rotate(p);
                            change(p), change(p[pre]), change(uncle);
                            rotate(p);
                        }
                        return;
                    }
                }
            }
            void clear(int p)
            {
                pre[p] = son[p][0] = son[p][1] = size[p] = cnt[p] = 0;
            }
            int apply()
            {
                clear(++tot);
                return tot;
            }
            void print(int p)
            {
                if (!p)
                    return;
                print(son[p][0]);
                for (int i = 1; i <= cnt[p]; i++)
                    std::cout << val[p] << ' ';
                print(son[p][1]);
            }

        public:
            RBTree() : root(0), tot(0)
            {
                memset(pre, 0, sizeof(pre));
                memset(son, 0, sizeof(son));
                memset(size, 0, sizeof(size));
                memset(cnt, 0, sizeof(cnt));
                memset(val, 0, sizeof(val));
                memset(colour, 0, sizeof(colour));
            }
            void insert(T val)
            {
                if (!root)
                {
                    root = apply();
                    colour[root] = RED;
                    cnt[root] = size[root] = 1;
                    this->val[root] = val;
                    return;
                }
                int cur = root, pre = 0;
                while (true)
                {
                    if (this->val[cur] == val)
                    {
                        cnt[cur]++;
                        size[cur]++;
                        return;
                    }
                    pre = cur, cur = son[pre][this->val[pre] < val];
                    if (!cur)
                    {
                        cur = apply();
                        this->pre[cur] = pre;
                        son[pre][this->val[pre] < val] = cur;
                        colour[cur] = RED;
                        maintain_insert(cur);
                        return;
                    }
                }
            }
            void print() { print(root); }
#undef RED
#undef BLACK
        };
    }
}
DS::BalancedTree::RBTree rbt;
int a[DS::BalancedTree::N];
int main()
{
    int n;
    std::cin >> n;
    for (int i = 1; i <= n; i++)
    {
        std::cin >> a[i];
        rbt.insert(a[i]);
    }
    std::sort(a + 1, a + 1 + n);
    for (int i = 1; i <= n; i++)
        std::cout << a[i] << ' ';
    std::cout << std::endl;
    rbt.print();
    std::cout << std::endl;
    return 0;
}