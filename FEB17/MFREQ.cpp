# include <bits/stdc++.h>
# include <ext/pb_ds/assoc_container.hpp>
# include <ext/pb_ds/tree_policy.hpp>
# include <boost/multiprecision/cpp_int.hpp>
using namespace std;
using namespace __gnu_pbds;
namespace vl = boost::multiprecision;

// Did you miss me ?

# define gc          getchar
# define LL          long long
# define VLL         vl::cpp_int
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
typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;
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


int group[100001], whichgroup[100001], gs[100001], ge[100001];
LL a[100001];

int main()
{
	int t;
	//in(t);
	t = 1;
	while (t--) {
        int n, m;
        in(n);
        in(m);
        int gn = 1;
        for (int i = 1; i <= n; i++)
        {
        	in(a[i]);
        	if (i == 1)
        	{
        		group[gn]++;
        		whichgroup[i] = gn;
				gs[gn] = 1;
        	}
        	else
        	{
        		if (a[i] == a[i - 1])
        		{
        			group[gn]++;
        			whichgroup[i] = gn;
        		}
        		else
        		{
					ge[gn] = i - 1;
        			gn++;
					gs[gn] = i;
        			group[gn]++;
        			whichgroup[i] = gn;
        		}
        	}
        }
		ge[gn] = n;
        LL l, r
		int k;
        while (m--)
        {
        	in(l);
        	in(r);
        	in(k);
        	LL idx = (r + l) / 2;
			int len = r - l + 1;
			gn = whichgroup[idx];
			if (len & 1)
			{
				if ( min(r, ge[gn]) - max(gs[gn], l) + 1 >= k)
					cout << a[idx] << "\n";
				else
				 	cout << "-1\n";
			}

			else
			{
				if (a[idx] != a[idx + 1])
					cout << "-1\n";
				else if (min(r, ge[gn]) - max(gs[gn], l) + 1 >= k)
					cout << a[idx] << "\n";
				else
					cout << "-1\n";
			}
        }

	}
    return 0;
}
