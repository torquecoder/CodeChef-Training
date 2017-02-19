# include <bits/stdc++.h>
//# include <ext/pb_ds/assoc_container.hpp>
//# include <ext/pb_ds/tree_policy.hpp>
//# include <boost/multiprecision/cpp_int.hpp>
using namespace std;
//using namespace __gnu_pbds;
//namespace vl = boost::multiprecision;
 
// Did you miss me ?
 
# define gc          getchar
# define LL          long long
//# define VLL         vl::cpp_int
# define pb          push_back
# define mp          make_pair
# define vi          vector<int>
# define vll         vector<LL>
# define pii         pair<int,int>
# define all(v)      v.begin(),v.end()
 
const int MOD = 1000000007;
const int MAXN = 1e6 + 5;
const int INF = 1e9;
const double PI = 3.14159265359;
 
template<class T> void in(T &x) { register T c=gc();x=0;T neg=0;for(;((c<48||c>57)&&c!='-');c=gc());if(c=='-'){neg=1;c=gc();}for(;c>47&&c<58;c=gc()){x=(x<<1)+(x<<3)+c-48;}if(neg)x=-x;}
//typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;
LL power(LL a,LL b,LL m){ if(b==0) return 1; if(b==1) return a%m; LL t=power(a,b/2,m); t=(t*t)%m; if(b&1)t=(t*a)%m; return t;}
LL lcm(LL a, LL b) { LL ret = a*b; ret /= __gcd(a,b); return ret;}
LL nC2(LL n) {LL ret = n*(n-1)/2; return ret;}
 
vector<int> primes;
void sieve(int n)
{
	bool isPrime[n + 1];
	memset(isPrime, true, sizeof(isPrime));
	isPrime[0] = isPrime[1] = false;
	for(int i = 2; i * i <= n; i++) {
		if (isPrime[i]) {
			for (int j = 2 * i; j <= n; j += i)
			 	isPrime[j] = false;
		}
	}
	for (int i = 2; i <= n; i++)
		if (isPrime[i])
			primes.push_back(i);
}
 
int n, f;
LL penalty;
int limit[200][200], grid[200][200], lastused[200][200], regrow[200][200], val, ul[200][200], ul_h[200][200], ul_v[200][200], gone[200][200];
LL flowers[200][200], ul_f[200][200];
bool valid (int i, int j, int tim)
{
	if (i >= 1 && i <= n && j >= 1 && j <= n && grid[i][j] == val && limit[i][j] > 0 && tim - lastused[i][j] - 1 >= regrow[i][j])
		return true;
	return false;
}
 
bool valid_ws (int i, int j, int tim)
{
	if (i >= 1 && i <= n && j >= 1 && j <= n && grid[i][j] == val && limit[i][j] > 0)
		return true;
	return false;
}
 
void traverse_ul(int x, int y, int px, int py, int M, int N)
{
	vector<pii> v;
	int i, k = 0, l = 0;
    int MM = M, NN = N;
    while (k < M && l < N)
    {
        for (i = l; i < N; ++i)
		{
		    assert(grid[k + x][i + y] == 1);
		    v.pb({k + x, i + y});
		}
        k++;
        for (i = k; i < M; ++i)
		{
		    assert(grid[i + x][N - 1 + y] == 1);
		    v.pb({i + x, N - 1 + y});
		}
        N--;
        if ( k < M)
        {
            for (i = N - 1; i >= l; --i)
			{
		        assert(grid[M - 1 + x][i + y] == 1);
				v.pb({M - 1 + x, i + y});
			}
            M--;
        }
        if (l < N)
        {
            for (i = M - 1; i >= k; --i)
			{
			    assert(grid[i + x][l + y] == 1);
			    v.pb({i + x, l + y});
			}
            l++;
        }
    }
 
	int sz = v.size();
	//cout<<"**"<<sz<<endl;
	//cout<<"**"<<M<<" "<<N<<endl;
	assert(sz == MM * NN);
	for (int i = 0; i < sz; i++)
		cout << "MOVE " << v[i].first << " " << v[i].second << "\n";
	for (int i = sz - 2; i >= 0; i--)
		cout << "MOVE " << v[i].first << " " << v[i].second << "\n";
	for (int i = 1; i < sz; i++)
		cout << "MOVE " << v[i].first << " " << v[i].second << "\n";
	for (int i = sz - 2; i >= 0; i--)
		cout << "MOVE " << v[i].first << " " << v[i].second << "\n";
	cout << "MOVE " << px << " " << py << "\n";
}
 
int main()
{
	int x, y;
	in(n), in(f), in(x), in(y), in(penalty);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			in(flowers[i][j]);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			in(limit[i][j]), assert(5 <= limit[i][j]);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			in(regrow[i][j]);
 
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			lastused[i][j] = -500;
	lastused[x][y] = 1;
    limit[x][y]--;
	for (int i = 0; i < f; i++)
	{
		int x1, y1, x2, y2;
		in(x1), in(y1), in(x2), in(y2);
		ul[x1][y1] = 1;
		ul_h[x1][y1] = y2 - y1 + 1;
		ul_v[x1][y1] = x2 - x1 + 1;
		LL ff = 0;
		for (int j = x1; j <= x2; j++)
		{
			for (int k = y1; k <= y2; k++)
			{
				grid[j][k] = 1;
				ff += flowers[j][k];
			}
		}
		ul_f[x1][y1] = ff;
	}
	val = grid[x][y];
	int tim = 2;
	while (1)
	{
		if (val == 0)
		{
			bool okeydokey = false;
			for (int dx = -1; dx <= 1; dx++)
			{
				for (int dy = -1; dy <= 1; dy++)
				{
					if (dx == 0 && dy == 0)	continue;
					if (ul[x + dx][y + dy]  && !gone[x + dx][y + dy] && limit[x][y] >= 1 && 3 * ul_f[x + dx][y + dy] > 2 * penalty)
					{
						traverse_ul(x + dx, y + dy, x, y, ul_v[x + dx][y + dy], ul_h[x + dx][y + dy]);
						gone[x + dx][y + dy] = 1;
						limit[x][y]--;
						okeydokey = true;
						break;
					}
				}
				if (okeydokey)
					break;
			}
		}
 
		bool ok = false;
		vector<pair<int, pair<int, int> > > v;
		for (int dx = -1; dx <= 1; dx++)
		{
			for (int dy = -1; dy <= 1; dy++)
			{
				if (dx == 0 && dy == 0)
					continue;
				if (valid(x + dx, y + dy, tim))
				{
					ok = true;
					v.pb({flowers[x + dx][y + dy], {x + dx, y + dy}});
				}
			}
		}
 
		if (ok)
		{
		    sort(all(v));
		    cout << "MOVE " << v[v.size() - 1].second.first << " " << v[v.size() - 1].second.second << "\n";
			x = v[v.size() - 1].second.first, y = v[v.size() - 1].second.second;
			limit[v[v.size() - 1].second.first][v[v.size() - 1].second.second]--;
			lastused[v[v.size() - 1].second.second][v[v.size() - 1].second.second] = tim;
		}
 
		if (!ok)
		{
			for (int dx = -1; dx <= 1; dx++)
			{
				for (int dy = -1; dy <= 1; dy++)
				{
					if (valid_ws(x + dx, y + dy, tim))
					{
						ok = true;
						cout << "MOVE " << x + dx << " " << y + dy << "\n";
						x += dx, y += dy;
						limit[x][y]--;
						break;
					}
				}
				if (ok)	break;
			}
			if(!ok)
			{
				cout << "EXIT\n";
				break;
			}
		}
		tim++;
	}
    return 0;
}