#include <iostream>
#include <random>
std::mt19937 rng(time(nullptr));
int rand(int max)
{
    return rng() % max + 1;
}
int main()
{
    freopen("in", "w", stdout);
    int n, m;
    n = rand(1000), m = rand(50000);
    std::cout << n << ' ' << m << std::endl;
    for (int i = 1; i <= n; i++)
        std::cout << rand(20) << ' ';
    std::cout << std::endl;
    for (int i = 1; i <= m; i++)
    {
        int l, r, x, op;
        op = rand(2), l = rand(n), r = rand(n), x = rand(10);
        if (l > r)
            std::swap(l, r);
        std::cout << op << ' ' << l << ' ' << r << ' ' << x << std::endl;
    }
    return 0;
}