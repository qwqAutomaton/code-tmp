#include <algorithm>
#include <iostream>
int a[110], b[110];
int main()
{
    int t;
    std::cin >> t;
    while (t--)
    {
        bool flag = false;
        int n;
        std::cin >> n;
        for (int i = 1; i <= n; i++)
            std::cin >> a[i];
        for (int i = 1; i <= n; i++)
            std::cin >> b[i];
        std::sort(a + 1, a + 1 + n);
        std::sort(b + 1, b + 1 + n);
        for (int i = 1; i <= n && !flag; i++)
            if (b[i] - a[i] != 0 && b[i] - a[i] != 1)
            {
                std::cout << "NO\n";
                flag = true;
            }
        if (!flag)
            std::cout << "YES\n";
    }
    return 0;
}