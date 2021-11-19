#include <iostream>
#include <cmath>
#include <cassert>
using ld = long double;
namespace ComputationalGeometry
{
    const int MAXN = 2e5 + 10;
    struct point
    {
        ld x, y;
        point(ld x = 0, ld y = 0) : x(x), y(y) {}
    } outer[MAXN], inner[MAXN];
    struct vector
    {
        ld x, y;
        vector() : x(0), y(0) {}
        vector(ld x, ld y) : x(x), y(y) {}
        vector(point a, point b) : x(b.x - a.x), y(b.y - a.y) {}
        ld operator*(const vector &v) const { return x * v.y - y * v.x; }
    };
    struct line
    {
        ld k, b;
        line(ld k, ld b) : k(k), b(b) {}
        line(point a, point b) : k((b.y - a.y) / (1.0 * b.x - a.x)), b(a.y - (b.y - a.y) / (1.0 * b.x - a.x) * a.x) {}
        ld getY(const ld &x) const { return k * x + b; }
        ld getX(const ld &y) const { return (y - b) / k; }
    };
    point intersect(line a, line b)
    {
        assert(a.k != b.k);
        return point((b.b - a.b) / (a.k - b.k), (b.b - a.b) / (a.k - b.k) * a.k + a.b);
    }
    bool haveIntersect(point a, point b, line l)
    {
        point c(1, l.getY(1));
        vector va(c, a), vb(c, b), vl(c, point(2, l.getY(2)));
        return (va * vl) * (vb * vl) < 0;
    }
    ld length[MAXN], totlen = 0;
    ld dist(point a, point b)
    {
        ld dx = a.x - b.x, dy = a.y - b.y;
        return sqrt(dx * dx + dy * dy);
    }
    int getNext(int i, int n) { return i % n + 1; }
    void calc(int n, int m)
    {
        // brute-force find the first two intersects
        int l = 1;
        do
        {
            totlen += dist(outer[l], outer[getNext(l, m)]);
            l = getNext(l, m);
        } while (l != 1);
        std::clog << "Totlen = " << totlen << std::endl;
        int cur = 1;
        l = 1;
        ld len = 0;
        line curLine(inner[cur], inner[getNext(cur, n)]);
        while (!haveIntersect(outer[l], outer[getNext(l, m)], curLine))
            l = getNext(l, m);
        int r = getNext(l, m);
        point inter1 = intersect(curLine, line(outer[l], outer[getNext(l, m)]));
        len += dist(inter1, outer[getNext(l, m)]);
        while (!haveIntersect(outer[r], outer[getNext(r, m)], curLine))
        {
            len += dist(outer[r], outer[getNext(r, m)]);
            r = getNext(r, m);
        }
        point inter2 = intersect(curLine, line(outer[r], outer[getNext(r, m)]));
        len += dist(inter1, outer[r]);
        if (inner[getNext(getNext(cur, n), n)].y > curLine.getY(inner[getNext(getNext(cur, n), n)].x))
            length[cur] = len;
        else
            length[cur] = totlen - len;
        std::clog << "Length[1]" << length[1] << std::endl;
        for (int i = 2; i != 1; i = getNext(i, n))
        {
            // std::clog << "Finding intersect of #" << i << std::endl;
            ld decr = 0, incr = 0;
            curLine = line(inner[i], inner[getNext(i, n)]);
            // std::clog << "Finding l bound" << std::endl;
            if (!haveIntersect(outer[l], outer[getNext(l, m)], curLine))
            {
                // std::clog << "quq" << std::endl;
                decr = dist(inter1, intersect(line(outer[l], outer[getNext(l, m)]), curLine));
                inter1 = intersect(line(outer[l], outer[getNext(l, m)]), curLine);
            }
            else
            {
                // std::clog << "qnq" << std::endl;
                decr = dist(inter1, outer[getNext(l, n)]);
                l = getNext(l, m);
                while (!haveIntersect(outer[l], outer[getNext(l, m)], curLine))
                {
                    decr += dist(outer[l], outer[getNext(l, m)]);
                    l = getNext(l, m);
                }
                inter1 = intersect(line(outer[l], outer[getNext(l, m)]), curLine);
                decr += dist(inter1, outer[l]);
            }
            // std::clog << "Finding r bound" << std::endl;
            if (!haveIntersect(outer[r], outer[getNext(r, m)], curLine))
            {
                // std::clog << "quq" << std::endl;
                incr = dist(inter2, intersect(line(outer[r], outer[getNext(r, m)]), curLine));
                inter2 = intersect(line(outer[r], outer[getNext(r, m)]), curLine);
            }
            else
            {
                // std::clog << "qnq" << std::endl;
                incr = dist(inter2, outer[getNext(r, m)]);
                r = getNext(r, m);
                while (!haveIntersect(outer[r], outer[getNext(r, m)], curLine))
                {
                    incr += dist(outer[r], outer[getNext(r, m)]);
                    r = getNext(r, n);
                }
                inter2 = intersect(line(outer[r], outer[getNext(r, m)]), curLine);
                incr += dist(inter2, outer[r]);
            }
            length[i] = length[i - 1] - decr + incr;
            std::clog << "Length[" << i << "] = " << length[i] << std::endl;
        }
    }
    ld calcExpect(int n, int m)
    {
        ld res = 0;
        int i = 1;
        do
        {
            res += dist(inner[i], inner[getNext(i, n)]) * length[i] / totlen;
            i = getNext(i, n);
        } while (i != 1);
        return res;
    }
}
int main()
{
    int n, m;
    std::cin >> n >> m;
    for (int i = 1, x, y; i <= n; i++)
    {
        std::cin >> x >> y;
        ComputationalGeometry::outer[i] = ComputationalGeometry::point(x, y);
    }
    for (int i = 1, x, y; i <= m; i++)
    {
        std::cin >> x >> y;
        ComputationalGeometry::inner[i] = ComputationalGeometry::point(x, y);
        std::clog << ComputationalGeometry::inner[i].x << std::endl;
    }
    std::clog << "Data read." << std::endl;
    ComputationalGeometry::calc(m, n);
    std::clog << "Preproccessed." << std::endl;
    printf("%.9Lf\n", ComputationalGeometry::calcExpect(m, n));
    return 0;
}
