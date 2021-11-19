#include <iostream>
#include <cstdlib>
int main()
{
    const int n = 10000;
    for (int i = 1; i <= n; i++)
    {
        if (i % 100 == 0)
            std::cout << "Tested " << i << " cases out of " << n << std::endl;
        system("gen.exe");
        system("cf896e.exe");
        if (system("4117.exe"))
        {
            std::cout << "RE on test #" << i << std::endl;
            std::cin.get();
        }
        if (system("fc ans out"))
        {
            std::cout << "WA on test #" << i << std::endl;
            std::cin.get();
        }
    }
}