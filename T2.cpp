#pragma GCC optimize("Ofast")
#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>
#define MAXN 1000010
#define int long long

inline void read(int &n)
{
	char chr = getchar();
	n = 0;
	while (!isdigit(chr))
		chr = getchar();
	while (isdigit(chr))
	{
		n = n * 10 + (chr & 15);
		chr = getchar();
	}
}

struct vertex
{
	int dfn, top, pre, size, hson, dep;
	std::vector<int> to;
	int val;
} ver[MAXN];
int rnk[MAXN], dfntot = 0;

void preproc(int cur)
{
	ver[cur].dep = ver[ver[cur].pre].dep + 1;
	ver[cur].size = 1;
	for (auto i : ver[cur].to)
	{
		ver[i].val += ver[cur].val;
		ver[i].pre = cur;
		preproc(i);
		ver[cur].size += ver[i].size;
		if (ver[i].size >= ver[ver[cur].hson].size)
			ver[cur].hson = i;
	}
}
void decomp(int cur, int top)
{
	ver[cur].top = top;
	ver[cur].dfn = ++dfntot;
	rnk[dfntot] = cur;
	if (!ver[cur].hson)
		return;
	decomp(ver[cur].hson, top);
	for (auto i : ver[cur].to)
		if (i ^ ver[cur].hson)
			decomp(i, i);
}

namespace DS
{
    int lower_bound(int left, int right, int key)
    {
        ; // todo
    }
	const int MAXSQRT = 1010;
	int blocklen, blockcnt = 1;
	int lpos[MAXSQRT], rpos[MAXSQRT], blocknum[MAXN];
	int sorted[MAXN], raw[MAXN], qzh[MAXN];
	inline void build(int n)
	{
		for (int i = 1; i <= n; i++)
			raw[i] = sorted[i] = ver[rnk[i]].val;
		blocklen = sqrt(n);
		lpos[1] = 1;
		int blocktot = 0;
		for (int i = 1; i <= n; i++)
		{
			blocktot++;
			if (blocktot > blocklen)
			{
				blocktot = 1;
				rpos[blockcnt++] = i - 1;
				lpos[blockcnt] = i;
			}
			blocknum[i] = blockcnt;
		}
		rpos[blockcnt] = n;
		for (int i = 1; i <= blockcnt; i++)
			std::sort(sorted + lpos[i], sorted + rpos[i] + 1);
        qzh[0] = 0;
        for (int i = 1; i <= n; i++)
            qzh[i] = qzh[i - 1] + sorted[i];
	}
	inline int querySum(int l, int r, int k, int delta) // \sum_{i=l}^r{a_i[a_i\geq k]}, where a_i = raw_i - delta
	{
		if (l > r) return 0; 
		int ans = 0;
		if (blocknum[l] >= blocknum[r]) // all not block
		{
			for (; l <= r; l++)
				ans += (raw[l] - delta) * (raw[l] - delta >= k);
			return ans;
		}
		for (; blocknum[l - 1] == blocknum[l]; l++)
			ans += (raw[l] - delta) * (raw[l] - delta >= k);
		for (; blocknum[r + 1] == blocknum[r]; r--)
			ans += (raw[r] - delta) * (raw[r] - delta >= k);
		signed lblock = blocknum[l];
		signed rblock = blocknum[r];
		for (; lblock <= rblock; lblock++)
        {
            signed pos = lower_bound(lpos[lblock], rpos[lblock] + 1, k + delta);
            (pos <= rpos[lblock]) && (ans += qzh[rpos[lblock]] - qzh[pos - 1] - delta * (rpos[lblock] - pos + 1));
        }
		return ans;
	}
}

signed main()
{
	int n, q;
	read(n);
	for (int i = 2; i <= n; i++)
	{
		read(ver[i].pre);
		read(ver[i].val);
		ver[ver[i].pre].to.push_back(i);
	}
	preproc(1);
	decomp(1, 1);
	DS::build(n);
	read(q);
	for (int i = 1, u, k; i <= q; i++)
	{
		read(u);
		read(k);
		printf("%lld\n", DS::querySum(ver[u].dfn + 1, ver[u].dfn + ver[u].size - 1, k, ver[u].val));
	}
	return 0;
}
