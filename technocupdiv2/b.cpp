#include <iostream>
#include <cstring>
int main()
{
    int t;
    std::cin >> t;
    while (t--)
    {
        int n, m;
        std::cin >> n >> m;
        if (n < m)
            std::swap(n, m);
        if (n == 2 && m == 2) std::cout << 2 << std::endl;
        else
        {
            int tmp = n * m;
            std::cout << (tmp / 3) + (tmp % 3 == 0 ? 0 : 1) << std::endl;
        }
    }
}