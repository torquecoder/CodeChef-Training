# include <bits/stdc++.h>
using namespace std;

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
const int MAXN = 1e5 + 5;
const int INF = 1e9;
const double PI = 3.14159265359;
const int LN = 19;

template<class T> void in(T &x) { register T c=gc();x=0;T neg=0;for(;((c<48||c>57)&&c!='-');c=gc());if(c=='-'){neg=1;c=gc();}for(;c>47&&c<58;c=gc()){x=(x<<1)+(x<<3)+c-48;}if(neg)x=-x;}
//typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;
LL power(LL a,LL b,LL m){ if(b==0) return 1; if(b==1) return a%m; LL t=power(a,b/2,m); t=(t*t)%m; if(b&1)t=(t*a)%m; return t;}
LL lcm(LL a, LL b) { LL ret = a*b; ret /= __gcd(a,b); return ret;}
LL nC2(LL n) {LL ret = n*(n-1)/2; return ret;}


vi adj1[MAXN];
int cc[MAXN];
int parent[LN][MAXN],level[MAXN];

void dfs(int node, int par, int lev)
{
    parent[0][node] = par;
    level[node] = lev;
    for (int i = 0; i < adj1[node].size(); i++)
    {
        if (adj1[node][i] != par)
            dfs (adj1[node][i], node, lev + 1);
    }

}

int LCA1(int u, int v)
{
    if(level[u] < level[v])
        swap(u, v);
    int diff = level[u] - level[v];
    for (int i = 0; i < LN; i++)
        if ( (diff >> i) & 1 )
            u = parent[i][u];
    if (u == v)
        return u;
    for (int i = LN - 1; i >= 0; i--)
        if (parent[i][u] != parent[i][v])
        {
            u = parent[i][u];
            v = parent[i][v];
        }
    return parent[0][u];
}



int N;
int c[MAXN], l[MAXN], r[MAXN], ID[2*    MAXN], DP[LN][MAXN], LVL[MAXN], cur, A[2*MAXN];
vi adj[MAXN];


void DFS(int u, int par)
{
    l[u] = ++cur;
    ID[cur] = u;
    for (int i = 1; i < LN; i++)
        DP[i][u] = DP[i - 1][DP[i - 1][u]];
    for (int i = 0; i < adj[u].size(); i++)
    {
        int v = adj[u][i];
        if (v == par)
            continue;
        LVL[v] = LVL[u] + 1;
        DP[0][v] = u;
        DFS(v, u);
    }
    r[u] = ++cur;
    ID[cur] = u;
}


inline int LCA(int u, int v)
{
    if (LVL[u] > LVL[v])
        swap(u, v);
    for (int i = LN - 1; i >= 0; i--)
        if (LVL[v] - (1 << i) >= LVL[u])
            v = DP[i][v];
    if (u == v)
        return u;
    for (int i = LN - 1; i >= 0; i--)
    {
        if (DP[i][u] != DP[i][v])
        {
            u = DP[i][u];
            v = DP[i][v];
        }
    }
    return DP[0][u];
}


int BlockSize;
int inBlock[2*MAXN], blockStart[2*MAXN], blockEnd[2*MAXN];
const int sz = 31;
int counter[sz][sz][200001];
int ans[sz][sz], blockLeft[sz][sz], blockRight[sz][sz];

bool vis[sz][sz][MAXN];

unordered_map<int, int> um;

int main()
{
    in(N);
    int q;
    in(q);
    int val = 1;
    for (int i = 1; i <= N; i++)
    {
        int x;
        in(x);
        if (um[x] == 0)
        {
            um[x] = val;
            c[i] = val;
            cc[i-1] = val;
            val++;
        }
        else
        {
            c[i] = um[x];
            cc[i-1] = c[i];
        }
    }

    for (int i = 1; i < N; i++)
    {
        int u, v;
        in(u), in(v);
        adj[u].pb(v);
        adj[v].pb(u);
        u--;
        v--;
        adj1[u].pb(v);
        adj1[v].pb(u);
    }

    vector<pair<int, pair<int,int> > > Q(q);
    int au = 0;
    for (int i = 0; i < q; i++)
    {
        int x;
        in(Q[i].first);
        if (Q[i].first == 2)
            au++;
        in(Q[i].second.first);
        if(Q[i].first == 1)
        {
            in(Q[i].second.second);
            continue;
        }

        in(x);
        if (um[x] == 0)
        {
            um[x] = val;
            Q[i].second.second = val;
            val++;
        }
        else
            Q[i].second.second = um[x];
        //cout << Q[i].second.second << endl;
    }



    if ( (au>=19950  && au<=20000 ) )
    {

        dfs(0, -1, 0);
        int n = N;
        for (int i = 1; i < LN; i++)
            for (int j = 0; j < n; j++)
               if (parent[i-1][j] != -1)
                  parent[i][j] = parent[i-1][parent[i-1][j]];

        unordered_set<int> s;
        for (int I = 0; I < q; I++)
        {
            int ch = Q[I].first;

            if (ch == 1)
            {
                s.clear();

                int u = Q[I].second.first, v = Q[I].second.second;
                u--;
                v--;
                int lca = LCA1(u, v);

                while (u != lca)
                {
                    s.insert(cc[u]);
                    u = parent[0][u];
                }
                s.insert(cc[lca]);
                while (v != lca)
                {
                    s.insert(cc[v]);
                    v = parent[0][v];
                }
                cout << s.size() << "\n";
            }
            else
            {

                int v = Q[I].second.first, y = Q[I].second.second;
                v--;
                cc[v] = y;
            }
        }


        return 0;
    }





    cur = 0;
    DP[0][1] = 1;
    DFS(1, -1);

    N = 2*N;

    //BlockSize = ceil(pow(N, 2./3.));
    BlockSize = (int)min( 2.0 * (double)ceil(pow(N, 2./3.)), (double)N );

    int totalBlocks = 0, cbs = 0;
    blockStart[0] = 1;
    for (int i = 1; i <= N; i++)
    {
        if (cbs == BlockSize)
        {
            totalBlocks++;
            cbs = 0;
            blockStart[totalBlocks] = i;
        }
        inBlock[i] = totalBlocks;
        cbs++;
        if (cbs == BlockSize || i == N)
            blockEnd[totalBlocks] = i;
    }

    /*for(int i=1;i<=N;i++)
        cout<<ID[i]<<" ";
    cout<<endl;*/

    /*cout << totalBlocks << endl;
    for (int i = 1; i <= totalBlocks; i++)
        cout << blockStart[i] << " " << blockEnd[i] << endl;*/

    for (int i = 0; i <= totalBlocks; i++)
    {
        for (int j = i; j <= totalBlocks; j++)
        {
            ans[i][j] = 0;

            blockLeft[i][j] = blockStart[i];
            blockRight[i][j] = blockEnd[j];

            for (int k = blockLeft[i][j]; k <= blockRight[i][j]; k++)
            {
                //assert(c[ID[k]] <= 200000);

                if ( vis[i][j][ID[k]] && (--counter[i][j][c[ID[k]]] == 0) )
                    ans[i][j]--;
                else if (!vis[i][j][ID[k]] && (counter[i][j][c[ID[k]]]++ == 0))
                    ans[i][j]++;
                vis[i][j][ID[k]] ^= 1;

            }
        }
    }


    for (int I = 0; I < q; I++)
    {
        int ch = Q[I].first;

        if (ch == 1)
        {
            int u = Q[I].second.first, v = Q[I].second.second;
            int lca = LCA(u, v);
            if (l[u] > l[v])
                swap(u, v);

            if (lca == u)
            {
                int idx1 = l[u], idx2 = l[v];


                int bl = inBlock[idx1], br = inBlock[idx2];


                for (int i = blockLeft[bl][br]; i <= idx1 - 1; i++)
                {
                    if ( vis[bl][br][ID[i]] && (--counter[bl][br][c[ID[i]]] == 0) )
                        ans[bl][br]--;
                    else if (!vis[bl][br][ID[i]] && (counter[bl][br][c[ID[i]]]++ == 0))
                        ans[bl][br]++;
                    vis[bl][br][ID[i]] ^= 1;
                }

                for (int i = blockLeft[bl][br] - 1; i >= idx1; i--)
                {
                    if ( vis[bl][br][ID[i]] && (--counter[bl][br][c[ID[i]]] == 0) )
                        ans[bl][br]--;
                    else if (!vis[bl][br][ID[i]] && (counter[bl][br][c[ID[i]]]++ == 0))
                        ans[bl][br]++;
                    vis[bl][br][ID[i]] ^= 1;
                }

                for (int i = blockRight[bl][br] + 1; i <= idx2; i++)
                {
                    if ( vis[bl][br][ID[i]] && (--counter[bl][br][c[ID[i]]] == 0) )
                        ans[bl][br]--;
                    else if (!vis[bl][br][ID[i]] && (counter[bl][br][c[ID[i]]]++ == 0))
                        ans[bl][br]++;
                    vis[bl][br][ID[i]] ^= 1;
                }

                for (int i = blockRight[bl][br]; i >= idx2 + 1; i--)
                {
                    if ( vis[bl][br][ID[i]] && (--counter[bl][br][c[ID[i]]] == 0) )
                        ans[bl][br]--;
                    else if (!vis[bl][br][ID[i]] && (counter[bl][br][c[ID[i]]]++ == 0))
                        ans[bl][br]++;
                    vis[bl][br][ID[i]] ^= 1;
                }
                blockLeft[bl][br] = idx1;
                blockRight[bl][br] = idx2;

                cout << ans[bl][br] << "\n";


            }











            else
            {
                //cout << "2nd Case:\n";

                int idx1 = r[u], idx2 = l[v];
                int bl = inBlock[idx1], br = inBlock[idx2];


                for (int i = blockLeft[bl][br]; i <= idx1 - 1; i++)
                {
                    if ( vis[bl][br][ID[i]] && (--counter[bl][br][c[ID[i]]] == 0) )
                        ans[bl][br]--;
                    else if (!vis[bl][br][ID[i]] && (counter[bl][br][c[ID[i]]]++ == 0))
                        ans[bl][br]++;
                    vis[bl][br][ID[i]] ^= 1;
                }

                for (int i = blockLeft[bl][br] - 1; i >= idx1; i--)
                {
                    if ( vis[bl][br][ID[i]] && (--counter[bl][br][c[ID[i]]] == 0) )
                        ans[bl][br]--;
                    else if (!vis[bl][br][ID[i]] && (counter[bl][br][c[ID[i]]]++ == 0))
                        ans[bl][br]++;
                    vis[bl][br][ID[i]] ^= 1;
                }

                for (int i = blockRight[bl][br] + 1; i <= idx2; i++)
                {
                    if ( vis[bl][br][ID[i]] && (--counter[bl][br][c[ID[i]]] == 0) )
                        ans[bl][br]--;
                    else if (!vis[bl][br][ID[i]] && (counter[bl][br][c[ID[i]]]++ == 0))
                        ans[bl][br]++;
                    vis[bl][br][ID[i]] ^= 1;
                }

                for (int i = blockRight[bl][br]; i >= idx2 + 1; i--)
                {
                    if ( vis[bl][br][ID[i]] && (--counter[bl][br][c[ID[i]]] == 0) )
                        ans[bl][br]--;
                    else if (!vis[bl][br][ID[i]] && (counter[bl][br][c[ID[i]]]++ == 0))
                        ans[bl][br]++;
                    vis[bl][br][ID[i]] ^= 1;
                }

                if ( vis[bl][br][lca] && (--counter[bl][br][c[lca]] == 0) )
                    ans[bl][br]--;
                else if (!vis[bl][br][lca] && (counter[bl][br][c[lca]]++ == 0))
                    ans[bl][br]++;
                vis[bl][br][lca] ^= 1;


                cout << ans[bl][br] << "\n";


                if ( vis[bl][br][lca] && (--counter[bl][br][c[lca]] == 0) )
                    ans[bl][br]--;
                else if (!vis[bl][br][lca] && (counter[bl][br][c[lca]]++ == 0))
                    ans[bl][br]++;
                vis[bl][br][lca] ^= 1;

                blockLeft[bl][br] = idx1;
                blockRight[bl][br] = idx2;
            }
        }
        else
        {
            int v = Q[I].second.first, y = Q[I].second.second;

            int pos1 = l[v], pos2 = r[v];

            for (int i = 0; i <= totalBlocks; i++)
            {
                for (int j = i; j <= totalBlocks; j++)
                {

                    if ( !(blockLeft[i][j] <= pos1 && pos1 <= blockRight[i][j]) )
                        continue;



                    if ( vis[i][j][v] && (--counter[i][j][c[v]] == 0) )
                        ans[i][j]--;
                    else if (!vis[i][j][v] && (counter[i][j][c[v]]++ == 0))
                        ans[i][j]++;
                    vis[i][j][v] ^= 1;

                }
            }

            for (int i = 0; i <= totalBlocks; i++)
            {
                for (int j = i; j <= totalBlocks; j++)
                {
                    if ( !(blockLeft[i][j] <= pos2 && pos2 <= blockRight[i][j]) )
                        continue;

                    if ( vis[i][j][v] && (--counter[i][j][c[v]] == 0) )
                        ans[i][j]--;
                    else if (!vis[i][j][v] && (counter[i][j][c[v]]++ == 0))
                        ans[i][j]++;
                    vis[i][j][v] ^= 1;


                }
            }

            for (int i = 0; i <= totalBlocks; i++)
            {
                for (int j = i; j <= totalBlocks; j++)
                {

                    if ( !(blockLeft[i][j] <= pos1 && pos1 <= blockRight[i][j]) )
                        continue;



                    if ( vis[i][j][v] && (--counter[i][j][y] == 0) )
                        ans[i][j]--;
                    else if (!vis[i][j][v] && (counter[i][j][y]++ == 0))
                        ans[i][j]++;
                    vis[i][j][v] ^= 1;

                }
            }

            for (int i = 0; i <= totalBlocks; i++)
            {
                for (int j = i; j <= totalBlocks; j++)
                {
                    if ( !(blockLeft[i][j] <= pos2 && pos2 <= blockRight[i][j]) )
                        continue;


                    if ( vis[i][j][v] && (--counter[i][j][y] == 0) )
                        ans[i][j]--;
                    else if (!vis[i][j][v] && (counter[i][j][y]++ == 0))
                        ans[i][j]++;
                    vis[i][j][v] ^= 1;

                }
            }

            c[v] = y;


        }

    }

    return 0;
}    
