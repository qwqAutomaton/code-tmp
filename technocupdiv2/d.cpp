#include <iostream>
#include <cmath>
long long query(int l, int r)
{
    std::cout << "? " << l << " " << r << std::endl;
    long long ret;
    std::cin >> ret;
    if (ret < 0)
        throw 1;
    return ret;
}
void answer(int i, int j, int k)
{
    std::cout << "! " << i << " " << j << " " << k << std::endl;
}
int getL(int l, int r)
{
    while (true)
    {
        if (l == r)
            return l;
        int mid = (l + r + 1) >> 1;
        if (query(l, mid))
            r = mid - 1;
        else
            l = mid;
    }
    return l;
}
int getR(int l, int r)
{
    while (true)
    {
        if (l == r)
            return l;
        int mid = (l + r) >> 1;
        if (query(mid, r))
            l = mid + 1;
        else
            r = mid;
    }
}
int getMid(int l, int r)
{
    while (true)
    {
        if (l == r)
            return l;
        int mid = (l + r + 1) >> 1;
        long long tot = query(l, mid), len = (mid - l + 1);
        if (tot == len * (len - 1) / 2)
            l = mid;
        else
            r = mid - 1;
    }
}
void interact()
{
    try
    {
        int n;
        std::cin >> n;
        int left = getL(1, n);
        int right = getR(left + 2, n);
        int middle = getMid(left + 1, right - 1);
        answer(left, middle + 1, right);
    }
    catch (int &i)
    {
        exit(0);
    }
}
int main()
{
    int t;
    std::cin >> t;
    while (t--)
        interact();
    return 0;
}