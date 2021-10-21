#include <iostream>
#include <cstring>
#include <bit>
using ull = unsigned long long;
const int MAXN = 15625010; // 1e9 / 64
ull bits[MAXN], pref1[70], suff1[70];
inline int getL(int num) { return (num - 1) * 64 + 1; }
inline int getR(int num) { return num * 64; }
int assign0(int l, int r)
{
    int lblock = (l - 1) / 64 + 1, rblock = (r - 1) / 64 + 1;
    if (lblock ^ rblock)
    {
        int lblockr = getR(lblock), rblockl = getL(rblock);
        
    }
    else
    {
        ull val = pref1[r] & suff1[l];
        ull change = val ^ bits[lblock];
        bits[lblock] = val;
        return __builtin_popcountll(change);
    }
}
int main()
{
    memset(bits, 0xff, sizeof(bits));
    suff1[0] = 0;
    for (int i = 1; i <= 64; i++)
        suff1[i] = suff1[i - 1] << 1 | 1;
    for (int i = 0; i <= 64; i++)
        pref1[i] = ~suff1[64 - i];
    int n, q;
    std::cin >> n >> q;
    for (int i = 1, k, l, r; i <= q; i++)
    {
        std::cin >> k >> l >> r;
        switch (k)
        {
        case 1:
            n -= assign0(l, r);
            std::cout << n << '\n';
            break;
        case 2:
            n += assign1(l, r);
            std::cout << n << '\n';
            break;
        default:
            std::cerr << "qwq" << std::endl;
            return -1;
            break;
        }
    }
    return 0;
}