function qpow(a, b, m)
{
    let res = 1;
    a %= m;
    while (b != 0)
    {
        if (b & 1)
            res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}
console.log(qpow(4, 20101007, 20101009));

