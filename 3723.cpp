#include <iostream>
#include <complex>
using comp = std::complex<long double>;
const int MAXN = 500010;
namespace DFT
{
int tr[MAXN << 3];
void FFT(comp *f, int n, bool rev = false)
{
    tr[0] = 0;
    for (int i = 1; i <= n; i++)
        tr[i] = (tr[i >> 1] >> 1) | (i & 1 ? n >> 1 : 0);
    for (int l = 2; l <= n; l <<= 1)
    {
        comp omega(cos(2 * M_PI / l), sin(2 * M_PI * (rev ? -1 : 1) / l));
        for (int k = 0; k < n; k += l)
        {
            comp cur(1, 0);
            for (int i = k; i < k + (l >> 1); i++)
            {
                comp qwq = cur * f[i + (l >> 1)];
                f[i + (l >> 1)] = f[i] - qwq;
                f[i] += qwq;
                cur *= omega;
            }
        }
    }
    if (rev)
    {
        for (int i = 0; i < n; i++)
            f[i] /= n;
    }
}
}
comp f[MAXN << 3], g[MAXN << 3];
int n, m;
long long sqrsumF = 0, sqrsumG = 0, sumF = 0, sumG = 0;
int main()
{
    std::cin >> n >> m;
    for (int i = 0, a; i < n; i++)
    {
        std::cin >> a;
        f[i].real(a);
        sqrsumF += a * a;
        sumF += a;
    }
    for (int i = 0, a; i < n; i++)
    {
        std::cin >> a;
        g[n - i].real(a);
        g[n + n - i].real(a);
        sqrsumG += a * a;
        sumG += a;
    }
    int lim = 1;
    while (lim < 3 * n)
        lim <<= 1;
    DFT::FFT(f, lim);
    DFT::FFT(g, lim);
    for (int i = 1; i <= n; i++)
        f[i] *= g[i];
    DFT::FFT(f, lim, 1);
    long long mxval = -1;
    for (int i = n; i < n << 1; i++)
        mxval = std::max(mxval, (long long)(floor(f[i].real() + 0.5)));
    long long xval1 = floor((sumF - sumG) / n), xval2 = ceil((sumF - sumG) / n);
    long long ans = std::min(n * xval1 * xval1 + 2 * (sumF - sumG) * xval1, n * xval2 * xval2 + 2 * (sumF - sumG) * xval2) + sqrsumF + sqrsumG - mxval;
    std::cout << ans << std::endl;
    return 0;
}

