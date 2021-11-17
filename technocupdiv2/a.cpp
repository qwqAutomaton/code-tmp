#include <iostream>
int main()
{
    int t;
    std::cin >> t;
    while (t--)
    {
        int u, v;
        std::cin >> u >> v;
        u *= u, v *= v;
        std::cout << u << ' ' << -v << std::endl;
    }
    return 0;
}