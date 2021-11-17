#include <iostream>
const int MAXN = 1000010;
namespace LCT
{
    namespace Splay
    {
        int son[MAXN][2], fa[MAXN], size[MAXN], tag[MAXN];
        int val[MAXN];
#define ls son[p][0]
#define rs son[p][1]
        bool is_root(int p)
        {
            return (!fa[p]) || (son[fa[p]][0] != p && son[fa[p]][1] != p);
        }
        int get_son(int p)
        {
            return son[fa[p]][1] == p;
        }
        void push_down(int p)
        {
            if (p && tag[p])
            {
                tag[p] = 0;
                if (ls)
                    tag[ls] ^= 1;
                if (rs)
                    tag(rs) ^= 1;
                std::swap(ls, rs);
            }
        }
        void push_up(int p)
        {
            size[p] = 1;
            if (ls)
                size[p] += size[ls];
            if (rs)
                size[p] += size[rs];
        }
        void push_to_root(int p)
        {
            if (!is_root(p)) push_to_root(fa[p]);
            push_down(p);
        }
        void rotate(int p)
        {
            if (is_root(p))
                return;
            int q = fa[p], r = fa[fa[p]], dir = get_son(p);
            if (!is_root(q))
                son[r][get_son(q)] = p;
            son[q][dir] = son[p][dir ^ 1];
            if (son[q][dir])
                fa[son[q][dir]] = q;
            son[p][dir ^ 1] = q;
            fa[q] = p;
            fa[p] = r;
            push_up(q);
            push_up(p);
        }
        void splay(int p)
        {
            push_to_root(p);
            while (!is_root(p))
            {
                if (!is_root(fa[p]))
                    rotate(get_son(fa[p]) == get_son(p) ? fa[p] : p);
                rotate(p);
            }
        }
        int access(int p)
        {
            for (int q = 0; p; q = p, p = fa[p])
            {
                splay(p);
                rs = q;
                push_up(p);
            }
            return p;
        }
        void make_root(int p)
        {
            access(p);
            splay(p);
            
        }
#undef ls
#undef rs
    }
}