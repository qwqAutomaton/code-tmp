#include <iostream>
#include <fstream>
#include <cstdlib>
#include <random>
#include <ctime>
std::mt19937 rng(time(nullptr));
void gen()
{
    int n, m;
    // n = (rng() % 100000 + 100000) % 100000 + 1;
    // m = (rng() % 100000 + 100000) % 100000 + 1;
    n = 100000;
    m = 100000;
    std::ofstream fout("in");
    fout << n << ' ' << m << '\n';
    for (int i = 1; i <= n; i++)
    {
        int qwq = (rng() % 100000 + 100000) % 100000 + 1;
        fout << qwq << " \n"[i == n];
    }
    for (int i = 1; i <= m; i++)
    {
        int op, l, r, x;
        op = (rng() % 2 + 2) % 2 + 1;
        r = (rng() % n + n) % n + 1;
        l = (rng() % n + n) % n + 1;
        // l = 1;
        // r = n;
        x = (rng() % 100000 + 100000) % 100000 + 1;
        if (l > r)
            std::swap(l, r);
        fout << op << ' ' << l << ' ' << r << ' ' << x << '\n';
    }
    fout.flush();
    fout.close();
}
int main()
{
    // gen();
    int count = 5000;
    for (int i = 1; i <= count; i++)
    {
        // if (i % 1000 == 0) std::cout << "#" << std::flush;
        std::cout << "Case #" << i << ": \n";
        gen();
        std::cout << "Running block#2...\n";
        if (system("./cf896e.cpp.out"))
            std::cout << ">>> RE <<<\n";
        std::cout << "Running brute force...\n";
        system("./cf896e.bf.cpp.out");
        int ret = system("diff out ans");
        std::cout << "diff retval: " << ret << '\n';
        if (ret)
        {
            std::cout << ">>> \033[31mWA\033[0m@Case #\033[32m" << i << "\033[0m <<<\n";
            std::cin.get();
        }
    }
    return 0;
}