#include <vector>
template <typename T>
class Poly
{
private:
    std::vector<T> data;
    int len;
    virtual void DFT() = 0;

public:
    Poly() : len(0) { data.clear(); }
    Poly(int len)
    {
        data.clear();
        this->len = 1;
        while (this->len < len)
            this->len <<= 1;
        for (int i = 0; i < len; i++)
            data.push_back(0);
        data.resize(this->len);
    }
    Poly(int len, T val)
    {
        data.clear();
        this->len = 1;
        while (this->len < len)
            this->len <<= 1;
        for (int i = 0; i < len; i++)
            data.emplace_back(val[i]);
        data.resize(this->len);
    }
    Poly(const Poly &p) = default;
    Poly &operator+=(const Poly &p)
    {
        len = std::max(len, p.len);
        data.resize(len);
        for (int i = p.len; i < len; i++)
            data[i] = 0;
        for (int i = 0; i < p.len; i++)
            data[i] += p.data[i];
        return *this;
    }
    Poly &operator-=(const Poly &p)
    {
        len = std::max(len, p.len);
        data.resize(len);
        for (int i = p.len; i < len; i++)
            data[i] = 0;
        for (int i = 0; i < p.len; i++)
            data[i] -= p.data[i];
        return *this;
    }
};
template <typename T>
Poly<T> operator+(const Poly<T> &f, const Poly<T> &g)
{
    Poly<T> ret = f;
    ret += g;
    return ret;
}
template <typename T>
Poly<T> operator-(const Poly<T> &f, const Poly<T> &g)
{
    Poly<T> ret = f;
    ret -= g;
    return ret;
}