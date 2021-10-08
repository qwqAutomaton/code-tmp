#include <iostream>
#include <functional>
#include <vector>
#include <stack>
using func = std::function<void(int)>;
struct operation
{
    func f;
    int x;
    operation(func a, int v = 0)
        : f(a), x(v) {}
};
std::vector<operation> operations;
std::stack<int> st;
void NUM(int x)
{
}
void POP(int/*ignored*/)
{
}
void INV(int/*ignored*/)
{
}
void DUP(int/*ignored*/)
{
}
void SWP(int/*ignored*/)
{
}
void ADD(int/*ignored*/)
{
}
void SUB(int/*ignored*/)
{
}
void MUL(int/*ignored*/)
{
}
void DIV(int/*ignored*/)
{
}
void MOD(int/*ignored*/)
{
}
void END(int/*ignored*/)
{
}
void read()
{
    std::string s, op, extra;
    std::stringstream ss;
    std::getline(std::cin, op);
    while (1)
    {
        ss = stringstream(op);
        int x;
        ss >> s >> x;
        if (s == "NUM")
            operations.emplace_back(NUM, x);
        else if (s == "POP")
            operations.emplace_back(POP);
        else if (s == "INV")
            operations.emplace_back(INV);
        else if (s == "DUP")
            operations.emplace_back(DUP);
        else if (s == "SWP")
            operations.emplace_back(SWP);
        else if (s == "ADD")
            operations.emplace_back(ADD);
        else if (s == "SUB")
            operations.emplace_back(SUB);
        else if (s == "MUL")
            operations.emplace_back(MUL);
        else if (s == "DIV")
            operations.emplace_back(DIV);
        else if (s == "MOD")
            operations.emplace_back(MOD);
        else if (s == "END")
        {
            operations.emplace_back(END);
            break;
        }
        else
        {
            throw "ERROR";
            return;
        }
    }
}

