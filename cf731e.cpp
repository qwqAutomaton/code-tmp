#include <iostream>
int a[1000010], f[1000010];
int main()
{
    int sufmax = -1;
    int n;
    std::cin >> n;
    for (int i = 1; i <= n; i++)
    {
        std::cin >> a[i];
        a[i] += a[i - 1];
    }
    f[n] = sufmax = a[n];
    for (int i = n - 1; i >= 2; i--)
        f[i] = sufmax = std::max(sufmax, a[i] - f[i + 1]);
    std::cout << f[2] << std::endl;
    return 0;
}

