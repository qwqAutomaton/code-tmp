#include <iostream>

int next[30000010][2], tail = 0;

void insert(int num)
{
    int len = 30, cur = 0;
    while (len >= 0)
    {
        int &tmp = next[cur][num & (1 << len) ? 1 : 0];
        if (!tmp)
            tmp = ++tail;
        cur = tmp;
        len--;
    }
}
int query(int x)
{
    int len = 30, cur = 0;
    int ans = 0;
    while (len >= 0)
    {
        int bit = x & (1 << len) ? 1 : 0;
        ans <<= 1;
        if (next[cur][bit ^ 1])
        {
            cur = next[cur][bit ^ 1];
            ans |= 1;
        }
        else
            cur = next[cur][bit];
        len--;
    }
    return ans;
}
int a[1000010];
int main()
{
    int n;
    std::cin >> n;
    for (int i = 1; i <= n; i++)
    {
        std::cin >> a[i];
        insert(a[i]);
    }
    int ans = -1;
    for (int i = 1; i <= n; i++)
        ans = std::max(query(a[i]), ans);
    std::cout << ans << std::endl;
    return 0;
}

