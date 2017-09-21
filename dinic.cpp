#include <bits/stdc++.h>
using namespace std;

const int MAXN = 500+5 ;
const int INF = 1000000000 ;

struct edge
{
    int a, b, cap, flow , yo ;
};

int n,m,s,t,d[MAXN] , ptr[MAXN] ;
int capacityOfNode[MAXN]  ;
vector<edge>e;
vector<int>g[MAXN];

void addEdge(int a,int b,int cap)
{
    edge e1 = { a, b, cap, 0 , 1 } ;
    edge e2 = { b, a, 0  , 0 , 0 } ;
    g[a].push_back((int)e.size());
    e.push_back(e1);
    g[b].push_back((int)e.size());
    e.push_back(e2);
}

bool bfs()
{
    queue < int > Q ;
    Q.push(s);
    memset(d,-1,sizeof(d));
    d[s]=0 ;
    while (!Q.empty())
    {
        int u=Q.front() ;
        Q.pop() ;
        for(int i=0; i<g[u].size(); i++)
        {
            int id=g[u][i];
            int v=e[id].b;
            if(d[v]==-1&&e[id].flow<e[id].cap)
            {
                Q.push(v) ;
                d[v]=d[u]+1 ;
            }
        }
    }
    return d[t]!=-1 ;
}

int dfs(int u,int flow)
{
    if (!flow)  return 0 ;
    if ( u==t )  return flow ;
    for(int& i = ptr[u] ; i<g[u].size(); i++)
    {
        int id = g[u][i];
        int v =  e[id].b ;
        if ( d[v] != d[u]+1 )  continue ;
        int pushed = dfs (v,min (flow,e[id].cap-e[id].flow)) ;
        if (pushed)
        {
            e [id].flow+=pushed ;
            e [id^1].flow-=pushed ;
            return pushed ;
        }
    }
    return 0 ;
}

int dinic()
{
    int flow = 0 ;
    while(true)
    {
        if(!bfs())  break ;
        memset(ptr, 0 , sizeof(ptr)) ;
        while ( int pushed = dfs(s,INF ) )
            flow += pushed ;
    }
    return flow ;
}
bool color[MAXN] ;

void dfs2( int u )
{
    if(color[u]) return ;
    //cout << "coloring " << u << endl ;
    color[u] = true ;
    for( int i = 0 ; i < g[u].size() ; i++ )
    {
        int id = g[u][i] ;
        if( e[id].cap>e[id].flow  && e[id].yo )
            dfs2( e[id].b ) ;
    }
}

int main()
{
    int T , cs = 0 ;
    cin >> T ;
    while( cs < T )
    {
        cs++ ;
        for( int i = 0 ; i <= n ; i++  ) g[i].clear() ;
        e.clear() ;
        memset(color,0,sizeof(color)) ;

        int x, y , w ;
        cin >> n >> m ;
        for( int i = 1 ; i <= n ; i++ ) cin >> capacityOfNode[i] ;
        for( int i = 0 ; i < m ; i++ )
        {
            cin >> x >> y >> w ;
            addEdge(x,y,w) ;
        }
        s = 1 ;
        t = n ;
        int maxFlow = dinic()  ;
        dfs2(1) ;

//    for( int i = 0 ; i < e.size() ; i++ )
//    {
//        cout << e[i].a << " " << e[i].b << " " << e[i].flow << " "<<e[i].cap <<  endl ;
//    }
        vector < int > ans ;
        for( int i = 0 ; i < e.size() ; i++ )
        {
            if( color[e[i].a] && !color[e[i].b] && e[i].yo )
                ans.push_back(i) ;
        }
        cout << "number of edges : " << ans.size() << endl ;
        for( int i = 0 ; i < ans.size() ; i++ )
            cout << e[ans[i]].a << " " << e[ans[i]].b<< endl ;
        cout << endl << "minimum sum " << maxFlow << endl ;
    }
}


/*


6 9
0 1 2 3 4 5
1 2 5
2 4 8
1 3 12
3 2 5
3 4 9
3 5 4
4 5 3
4 6 7
5 6 8

*/
