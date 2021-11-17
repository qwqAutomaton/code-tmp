#include <iostream>
#include <vector>
const int MAXN = 3e5 + 10;
template <typename T = int, const unsigned MOD = 1000000007>
class ModNum
{
private:
	T x;

public:
	ModNum() : x(0) {}
	ModNum(T a) : x(a) {}
	ModNum operator+(const ModNum &m) const { return ModNum((x + m.x) % MOD); }
	ModNum operator-(const ModNum &m) const { return ModNum(((x - m.x) % MOD + MOD) % MOD); }
	ModNum operator*(const ModNum &m) const { return ModNum(x * m.x % MOD); }
	bool operator==(const ModNum &m) const { return x % MOD == m.x % MOD; }
	operator T() { return x % MOD; }
};
class Hash
{
private:
	typedef ModNum<long long, 1000000007> hv1;
	typedef ModNum<long long, 1000000009> hv2;
	hv1 h1;
	hv2 h2;

public:
	Hash(long long a, long long b) : h1(a), h2(b) {}
	Hash(long long a) : h1(a), h2(a) {}
	Hash() : h1(0), h2(0) {}
	Hash operator+(const Hash &h) const { return Hash(h1 + h.h1, h2 + h.h2); }
	Hash operator-(const Hash &h) const { return Hash(h1 - h.h1, h2 - h.h2); }
	Hash operator*(const Hash &h) const { return Hash(h1 * h.h1, h2 * h.h2); }
	bool operator==(const Hash &h) const { return h1 == h.h1 && h2 == h.h2; }
};
int dfn[MAXN], top[MAXN], dep[MAXN], val[MAXN], pre[MAXN], sz[MAXN], son[MAXN], rnk[MAXN], dfntot = 0;
std::vector<int> to[MAXN];
const Hash BASE(131, 13331);
Hash hash1[MAXN], hash2[MAXN], pows[MAXN];
void dfs1(int cur)
{
	dep[cur] = dep[pre[cur]] + 1;
	sz[cur] = 1, son[cur] = 0;
	for (auto i : to[cur])
	{
		if (i == pre[cur])
			continue;
		pre[i] = cur;
		dfs1(i);
		sz[cur] += sz[i];
		if (sz[i] > sz[son[cur]])
			son[cur] = i;
	}
}
void dfs2(int cur, int top)
{
	dfn[cur] = ++dfntot;
	rnk[dfntot] = cur;
	::top[cur] = top;
	if (!son[cur])
		return;
	dfs2(son[cur], top);
	for (auto i : to[cur])
		if (i != pre[cur] && i != son[cur])
			dfs2(i, i);
}
int LCA(int u, int v)
{
	while (top[u] != top[v])
	{
		if (dep[top[u]] < dep[top[v]])
			std::swap(u, v);
		u = pre[top[u]];
	}
	if (dep[u] < dep[v])
		std::swap(u, v);
	return v;
}
void preprocHash(int n)
{
	hash1[0] = 0, hash2[n + 1] = 0, pows[0] = 1;
	for (int i = 1; i <= n + 1; i++)
		pows[i] = pows[i - 1] * BASE;
	for (int i = 1; i <= n; i++)
		hash1[i] = hash1[i - 1] * BASE + val[rnk[i]];
	for (int i = n; i >= 1; i--)
		hash2[i] = hash2[i + 1] * BASE + val[rnk[i]];
}
Hash getHash(bool flag, int beg, int len)
{
	if (flag)
		return hash1[beg + len - 1] - hash1[beg - 1] * pows[len];
	return hash2[beg - len + 1] - hash2[beg + 1] * pows[len];
}
std::vector<std::pair<int, int>> get(int u, int v)
{
	int lca = LCA(u, v);
	std::vector<std::pair<int, int>> ret, tmp;
	ret.clear();
	tmp.clear();
	while (top[u] != top[lca])
	{
		ret.push_back(std::pair<int, int>(u, top[u]));
		u = pre[top[u]];
	}
	ret.push_back(std::pair<int, int>(u, lca));
	while (top[v] != top[lca])
	{
		tmp.push_back(std::pair<int, int>(top[v], v));
		v = pre[top[v]];
	}
	if (v != lca)
		tmp.push_back(std::pair<int, int>(son[lca], v));
	while (!tmp.empty())
	{
		ret.push_back(tmp.back());
		tmp.pop_back();
	}
	return ret;
}
int getLen(std::pair<int, int> pr)
{
	return abs(dep[pr.first] - dep[pr.second]) + 1;
}
int main()
{
#ifdef VSCODE_DEBUG
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
#endif
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);
	int n, m;
	std::cin >> n;
	std::string s;
	std::cin >> s;
	for (int i = 1; i <= n; i++)
		val[i] = s[i - 1];
	for (int i = 1, u, v; i < n; i++)
	{
		std::cin >> u >> v;
		to[u].push_back(v);
		to[v].push_back(u);
	}
	dep[1] = 1, pre[1] = 0;
	dfs1(1);
	dfs2(1, 1);
	preprocHash(n);
	std::cin >> m;
	for (int i = 1, a, b, c, d; i <= m; i++)
	{
		std::cin >> a >> b >> c >> d;
		unsigned ans = 0, s = 0, t = 0;
		auto p = get(a, b), q = get(c, d);
		while (s < p.size() && t < q.size())
		{
			auto f = p[s], g = q[t];
			int df = dfn[f.first], dg = dfn[g.first];
			bool ff = df < dfn[f.second], fg = dg < dfn[g.second];
			int lf = getLen(f), lg = getLen(g);
			int len = std::min(lf, lg);
			if (getHash(ff, df, len) == getHash(fg, dg, len))
			{
				if (lf == len)
					s++;
				else
					p[s].first = rnk[df + (ff ? 1 : -1) * len];
				if (lg == len)
					t++;
				else
					q[t].first = rnk[dg + (fg ? 1 : -1) * len];
				ans += len;
			}
			else
			{
				int l = 1, r = len;
				while (l < r)
				{
					int mid = (l + r) >> 1;
					if (getHash(ff, df, mid) == getHash(fg, dg, mid))
						l = mid + 1;
					else
						r = mid;
				}
				ans += l - 1;
				break;
			}
		}
		std::cout << ans << '\n';
	}
}
