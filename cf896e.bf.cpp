#include <iostream>
const int MAXN = 100010;
int a[MAXN];
int main()
{
    freopen("in", "r", stdin);
    freopen("ans", "w", stdout);
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int n, q;
    std::cin >> n >> q;
    for (int i = 1; i <= n; i++)
        std::cin >> a[i];
    for (int i = 1, op, l, r, x; i <= q; i++)
    {
        std::cin >> op >> l >> r >> x;
        if (op ^ 2)
        {
            for (; l <= r; l++)
                if (a[l] > x)
                    a[l] -= x;
        }
        else
        {
            int res = 0;
            for (; l <= r; l++)
                if (a[l] == x)
                    res++;
            std::cout << res << '\n';
        }
    }
    std::cout.flush();
    return 0;
}