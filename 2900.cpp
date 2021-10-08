#include <iostream>
#include <algorithm>
#include <queue>
const int MAXN = 100010;
struct land
{
    int w, h;
} l[MAXN];
int f[MAXN];// q[MAXN], head = 1, tail = 0;
void init(int &n)
{
    std::sort(l + 1, l + 1 + n, [](const land &a, const land &b) -> bool { return a.w == b.w ? a.h > b.h : a.w > b.w; });
    int tot = 0;
    for (int i = 1; i <= n; i++)
        if (l[tot].h < l[i].h)
            l[++tot] = l[i];
    n = tot;
}
double slope(int i, int j)
{
    return 1.0 * (f[i] - f[j]) / (l[j + 1].w - l[i + 1].w);
}
int main()
{
    int n;
    std::deque<int> q;
    std::cin >> n;
    for (int i = 1; i <= n; i++)
        std::cin >> l[i].w >> l[i].h;
    init(n);
    q.push_back(0);
    for (int i = 1; i <= n; i++)
    {
        while (q.size() > 1 && slope(q[0], q[1]) <= l[i].h)
            q.pop_front();
        f[i] = f[q.front()] + l[q.front() + 1].w * l[i].h;
        while (q.size() > 1 && slope(q[q.size() - 2], q.back()) >= slope(q.back(), i))
            q.pop_back();
        q.push_back(i);
    }
    std::cout << f[n];
    return 0;
}

