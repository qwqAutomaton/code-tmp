#include <iostream>
struct lim
{
    int val;
    bool eq;
} max, min;
void readmore(int &x)
{
    char chr = getchar();
    while (isdigit(chr))
    {
        x = x * 10 + (chr & 15);
        chr = getchar();
    }
}
int main()
{
    max.val = 2147483646;
    min.val = -2147483646;
    int n;
    char chr;
    std::cin >> n >> chr;
    for (int i = 1, x; i <= n; i++)
    {
        char tmp = getchar();
        while (tmp ^ chr) tmp = getchar();
        tmp = getchar();
        lim l;
        l.val = 0;
        if (tmp == '<')
        {
            tmp = getchar();
            if (tmp != '=')
            {
                l.eq = false;
                bool flag = false;
                if (tmp == '-')
                    flag = true;
                else
                    l.val = tmp & 15;
                readmore(l.val); 
                if (flag) l.val = -l.val;
                if (max.val < l.val)
                    continue;
                max = l;
            }
            else
            {
                l.eq = true;
                bool flag = false;
                tmp = getchar();
                if (tmp == '-')
                    flag = true;
                else
                    l.val = tmp & 15;
                readmore(l.val);
                if (flag) l.val = -l.val;
                if (max.val > l.val)
                    max = l;
            }
        }
        else
        {
            tmp = getchar();
            if (tmp != '=')
            {
                l.eq = false;
                bool flag = false;
                if (tmp == '-')
                    flag = true;
                else
                    l.val = tmp & 15;
                readmore(l.val);
                if (flag) l.val = -l.val;
                if (min.val > l.val)
                    continue;
                min = l;
            }
            else
            {
                l.eq = true;
                bool flag = false;
                tmp = getchar();
                if (tmp == '-')
                    flag = true;
                else
                    l.val = tmp & 15;
                readmore(l.val);
                if (flag) l.val = -l.val;
                if (min.val < l.val)
                    min = l;
            }
        }
    }
    if (max.val < min.val || (max.val == min.val && (!max.eq || !min.eq)))
        std::cout << "No Answer!\n";
    else
    {
#define inf 2147483646
        if (min.val != -inf && max.val != inf)
            std::cout << min.val << (min.eq ? "<=" : "<") << chr << (max.eq ? "<=" : "<") << max.val;
        else if (min.val == max.val)
            std::cout << chr << "=" << min.val;
        else if (min.val == -inf)
            std::cout << chr << (max.eq ? "<=" : "<") << max.val;
        else if (max.val == inf)
            std::cout << chr << (min.eq ? ">=" : ">") << min.val;
        else
            std::cout << chr << " in R";
    }
    std::cout << '\n';
    return 0;
}

