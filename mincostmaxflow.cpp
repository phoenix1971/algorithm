#include <bits/stdc++.h>

using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> ii;
typedef pair<double,double> dd;
typedef pair<char,char> cc;
typedef vector<ii> vii;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> l4;

typedef int LL;
const double eps = 0.005;
const int maxn = 20100;
const ll mod = 1e9+7;
const int INF = 1e9;


//mcmf
struct Edge {
    int from, to, cap, flow, cost;
};
struct MCMF {
    int n, m, s, t;
    vector<Edge> edges;
    vector<int> G[maxn];
    int inq[maxn];
    int d[maxn];
    int p[maxn];
    int a[maxn];
    void init(int n) {
        this->n = n;
        for(int i = 0; i < n; i++) G[i].clear();
        edges.clear();
    }
    void AddEdge(int from, int to, int cap, int cost) {
        //cout << from << " " << to << " " << cap << " " << cost << endl ;
        edges.push_back((Edge) {
            from, to, cap, 0, cost
        });
        edges.push_back((Edge) {
            to, from, 0, 0, -cost
        });
        m = edges.size();
        G[from].push_back(m-2);
        G[to].push_back(m-1);
    }
    bool BellmanFord(int s, int t, LL& ans) {
        for(int i = 0; i < n; i++) d[i] = INF;
        memset(inq, 0, sizeof(inq));
        d[s] = 0;
        inq[s] = 1;
        p[s] = 0;
        a[s] = INF;
        queue<int> Q;
        Q.push(s);
        while(!Q.empty()) {
            int u = Q.front();
            Q.pop();
            inq[u] = 0;
            for(int i = 0; i < G[u].size(); i++) {
                Edge& e = edges[G[u][i]];
                if(e.cap > e.flow && d[e.to] > d[u] + e.cost) {
                    d[e.to] = d[u] + e.cost;
                    p[e.to] = G[u][i];
                    a[e.to] = min(a[u], e.cap - e.flow);
                    if(!inq[e.to]) {
                        Q.push(e.to);
                        inq[e.to] = 1;
                    }
                }
            }
        }
        if(d[t] == INF) return false;
        ans += (LL)d[t] * (LL)a[t];
        int u = t;
        while(u != s) {
            edges[p[u]].flow += a[t];
            edges[p[u]^1].flow -= a[t];
            u = edges[p[u]].from;
        }
        return true;
    }
    LL Mincost(int s, int t) {  //requires that there will be no negative loop in the starting network
        LL cost = 0;
        while(BellmanFord(s, t, cost));
        return cost;
    }
};

MCMF flow;
int T,cs ;
int offset = 0 ;
int a[105][105] ;
int main() {
    scanf("%d",&T);
    int n,m;
    while ( cs < T ) {
        cs++;
        scanf("%d%d",&n,&m);
        for(int i = 0 ; i < n ; i++)for(int j = 0 ; j < m ; j++ )scanf("%d",&a[i][j] ) ;
        flow.init(2*n*m);
        int v = n*m ;
        for (int i = 0; i < v; i++) {
            if (i == 0) {
                flow.AddEdge(0, 1, 2, offset - a[0][0] );
            } else if (i == v-1) {
                flow.AddEdge(2*(v-1), 2*v-1, 2, offset - a[n-1][m-1] );
            } else {
                flow.AddEdge(2*i, 2*i+1, 1, offset - a[i/m][i%m] );
            }
        }
        for (int i = 0; i < n; i++) {
            for(int j = 0 ; j < m ; j++ ) {
                if(i!=n-1)flow.AddEdge(2*(i*m+j)+1, 2*((i+1)*m+j), 1, 0);
                if(j!=m-1)flow.AddEdge(2*(i*m+j)+1, 2*(i*m+j+1), 1, 0);
            }
        }
        int ret = flow.Mincost(0, 2*v-1) - ( offset-a[0][0] ) - ( offset - a[n-1][m-1]) ;

        printf("Case %d: %d\n",cs,-ret );
    }
    return 0;
}
