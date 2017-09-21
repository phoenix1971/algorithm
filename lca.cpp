
#include <bits/stdc++.h>
using namespace std ;

const int MAX_SIZE = 1e5 ;
int par[MAX_SIZE+7][25] ;
int st[MAX_SIZE+7], en[MAX_SIZE+7] ;
vector< int > adj[MAX_SIZE+7] ;
int _time ;
bool isPar(int u , int v)
{
    return ( st[u] <= st[v] && en[v] <= en[u] ) ;
}
int LCA(int u , int v)
{
    if(isPar(u,v))return u;
    if(isPar(v,u))return v;
    if(isPar(par[u][0],v)) return par[u][0] ;
    for(int i = 1 ; i < 20 ; i++ )
    {
        if(isPar(par[u][i],v))return LCA( par[u][i-1],v) ;
    }
}
void dfs(int u , int p=1 )
{
    st[u] = ++_time ;
    par[u][0] = p ;
    for( int i = 1 ; i <20 ; i++ )par[u][i] = par[par[u][i-1]][i-1] ;\
    for(int i = 0 ; i < adj[u].size();i++)
    {
        int v = adj[u][i];
        if(v!=p)dfs(v,u);
    }
    en[u] = ++_time ;
}
