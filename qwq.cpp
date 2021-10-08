#include <iostream>
#include <cstdlib>
#include <cstdio>
int main()
{
    char chr = getchar();
    while (chr && chr != EOF)
    {
        if (chr == '\\')
        {
            chr = getchar();
            if (chr == 'n')
            {
                std::cout << "linux";
                return 0;
            }
            else if (chr == 'r')
            {
                chr = getchar();
                if (chr != '\\')
                {
                    std::cout << "mac";
                    return 0;
                }
                else{ std::cout << "windows";return 0;}
            }
        }
        chr = getchar();
    }
}


