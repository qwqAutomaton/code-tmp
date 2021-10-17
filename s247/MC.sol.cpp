#include <bits/stdc++.h>
using namespace std;
#define rep(i , l , r) for(int i = (l) , ___ = (r) ; i <= ___ ; ++i)
#define per(i , r , l) for(int i = (r) , ___ = (l) ; i >= ___ ; --i)
template<typename T>inline T read(T &f)
{
	f = 0 ; int x = 1 ; char c = getchar();
	while(!isdigit(c)) x = c == '-' ? -1 : 1 , c = getchar();
	while(isdigit(c)) (f *= 10) += c & 15 , c = getchar();
	return f *= x;
}
template<typename T>inline int chkmin(T &x , const T &y) { return x > y ? x = y , 1 : 0 ; }
template<typename T>inline int chkmax(T &x , const T &y) { return x < y ? x = y , 1 : 0 ; }
const int N = 100000 + 5 , KCZ = 19260817;
const int M = 2000000 + 5;
int n , m , q , fac[M] , inv[M];
int T[N] , Y[N];
int C(int n , int m)
{
	if(n < m) return 0;
	return 1ll * fac[n] * inv[m] % KCZ * inv[n - m] % KCZ;
}
struct Edge
{
	int from , to;
} E[N];
struct Query
{
	int op;
	int X , T , Y; // 1
	int S , flag;  // 2
	int N; // 3
} Q[N];

int vis[N] , fa[N] , sz[N] , Su[N] , Ans[N];

inline int mp(int x , int y = KCZ - 2)
{
	int ret = 1;
	for( ; y ; y >>= 1 , x = 1ll * x * x % KCZ) y & 1 ? ret = 1ll * ret * x % KCZ : 0;
	return ret;
}

map<int , int> G[N];

int get(int u)
{
	return fa[u] == u ? u : fa[u] = get(fa[u]);
}

void merge(int u , int v)
{
	u = get(u) , v = get(v);
	if(u == v) return ;
	if(sz[u] < sz[v]) swap(u , v);
	fa[v] = u , sz[u] += sz[v];
	for(auto pi : G[v])
	{
		G[u][pi.first] += pi.second;
	}
	Su[u] += Su[v];
}

int main()
{
    freopen("data/mc/mc1.in", "r", stdin);
    freopen("data/mc/mc1.sol.ans", "w", stdout);
	read(n) , read(m) , read(q);
	rep(i , 1 , n)
	{
		read(T[i]) , read(Y[i]);
		G[i][Y[i]] += T[i];
		Su[i] += T[i];
	}
	rep(i , 1 , m)
	{
		static int u , v;
		read(u) , read(v);
		E[i] = {u , v};
	}
	rep(i , 1 , q)
	{
		static int op;
		read(op);
		if(op == 1)
		{
			Q[i].op = 1;
			read(Q[i].X) , read(Q[i].T) , read(Q[i].Y);
			G[Q[i].X][Q[i].Y] += Q[i].T;
			Su[Q[i].X] += Q[i].T;
		}
		else if(op == 2)
		{
			Q[i].op = 2;
			read(Q[i].S);
			if(!vis[Q[i].S]) Q[i].flag = 1 , vis[Q[i].S] = 1;
		}
		else
		{
			Q[i].op = 3;
			read(Q[i].X) , read(Q[i].N) , read(Q[i].Y);
		}
	}
	int L = 2000000;
	fac[0] = inv[0] = 1;
	rep(i , 1 , L) fac[i] = 1ll * fac[i - 1] * i % KCZ;
	inv[L] = mp(fac[L]);
	per(i , L , 1) inv[i - 1] = 1ll * inv[i] * i % KCZ;
	// cerr << C(3 , 1) << ' ' << C(10 , 2) << endl;
	rep(i , 1 , n) fa[i] = i , sz[i] = 1;
	rep(i , 1 , m) if(!vis[i])
	{
		int u = E[i].from , v = E[i].to;
		merge(u , v);
	}
	/*rep(i , 1 , n) if(get(i) == i)
	{
		cerr << i << " : \n";
		for(auto pi : G[i])
		{
			cerr << pi.first << "," << pi.second << " ";
		}
		cerr << endl;
	}*/
	per(i , q , 1)
	{
		if(Q[i].op == 1)
		{
			int u = get(Q[i].X);
			G[u][Q[i].Y] -= Q[i].T;
			Su[u] -= Q[i].T;
		}
		else if(Q[i].op == 2)
		{
			if(Q[i].flag)
			{
				merge(E[Q[i].S].from , E[Q[i].S].to);
			}
		}
		else
		{
			int u = get(Q[i].X);
			// cerr << G[u][Q[i].Y] << ' ' << Su[u] << ' ' << Q[i].N << endl;
			Ans[i] = 1ll * C(G[u][Q[i].Y] , Q[i].N) * mp(C(Su[u] , Q[i].N)) % KCZ;
		}
	}
	rep(i , 1 , q) if(Q[i].op == 3)
	{
		printf("%d\n" , Ans[i]);
	}
	return 0;
}

