#include <bits/stdc++.h>
using namespace std ;


int t , cs;
int Ans ;
vector <int> ans ;
int n , m , s[8003] ;
vector < int > bro[16005] ,orb[16005] ,scc[16005] , graph[16005] ;
int x, y ;
int ck[16005] , up[16005] ;
stack < int > Stack ;


void addEdge(int u , int v )
{
    int ux, vx, uy, vy  ;
    if( u > 0 ) ux = 2 * u -1 , uy = ux-1 ;
    else uy = 2 *( -u)-1 , ux = uy - 1 ;
    if( v > 0 ) vx = 2 * v -1 , vy = vx-1 ;
    else vy = 2 *( -v)-1 , vx = vy - 1 ;

    bro[uy].push_back(vx) ;
    bro[vy].push_back(ux) ;

    // cout << uy << " -> " << vx << endl ;
    // cout << vy << " -> " << ux << endl ;

    orb[vx].push_back(uy) ;
    orb[ux].push_back(vy) ;
}

void go(int u)
{
    if(ck[u] != -1 ) return ;
    ck[u] = 0 ;

    for(int i = 0 ; i < bro[u].size() ; i++ )
        go(bro[u][i]) ;

    Stack.push(u) ;
}

void go(int u, int id)
{
    if(ck[u] != 0 ) return ;
    ck[u] = id ;
   // cout << "u = " << u << " && ck[u] " << ck[u] << " && id " << id << endl ;
    scc[id].push_back(u) ;
    for(int i = 0 ; i < orb[u].size() ; i++ )
        go(orb[u][i], id ) ;
}

void graph_compression()
{
    int r = 2*m ;
    for( int u = 0 ; u < r  ; u++ )
    {
        for( int i = 0 ; i < bro[u].size() ; i++ )
        {
            int v = bro[u][i] ;
           // cout << "uv " << u << " " << v << endl ;
           //  cout << "ckuv " << ck[u] << " " << ck[v] << endl ;
            graph[ck[u]].push_back(ck[v]) ;
        }
    }
}

int theLastCalc(int u )
{
    if(ck[u]!=0) return up[u];
    ck[u] = 1 ;
   // cout << "sigh3" << endl ;
    for( int i = 0 ; i < graph[u].size() ; i++)
    {
        up[u] |= theLastCalc(graph[u][i] ) ;
    }
  //  cout <<"sigh4" << endl ;

    for( int i = 0 ; i < scc[u].size() ; i++ )
    {
        int ux = scc[u][i] | 1 ;
        ux = (ux+1) >> 1 ;
        if(s[ux] != -1 && (scc[u][i]&1) != s[ux]  )
        {
            up[u]  = 1 ;
            break ;
        }
    }
    for( int i = 0 ; i < scc[u].size() ; i++ )
    {
        int ux = scc[u][i] | 1 ;
        ux = (ux+1) >> 1 ;
        s[ux] = up[u]^(scc[u][i]&1) ;
    }
    return up[u] ;

}

int main()
{
    //freopen("input.txt", "r" , stdin ) ;
    scanf("%d",&t) ;

    while( cs < t)
    {
        cs++ ;
        ans.clear() ;
        Ans = 0 ;
        memset(s,-1,sizeof(s)) ;
        for( int i = 0 ; i < 16001 ; i++ )graph[i].clear() , bro[i].clear(), orb[i].clear() ,scc[i].clear() ;
        scanf("%d %d",&n, &m ) ;
        for( int i = 0 ; i < n ; i++ )
        {
            scanf("%d %d",&x,&y) ;
            addEdge(x,y) ;
        }
        memset(ck,-1,sizeof(ck));
        int r = 2*m ;
        for( int i = 0 ; i < r ; i++ )go(i) ;
        int cnt = 0 ;
        while(!Stack.empty())
        {
            int u = Stack.top() ;
         //   cout << "u " << u << endl ;
            Stack.pop() ;
            if(ck[u] == 0 )
            {
                ++cnt ;
                go(u,cnt) ;
            }
        }

        Ans = 1 ;
//        cout << "scc : " ;
//        for( int i = 0 ; i < r ; i++ )cout << ck[i] << " " ;
//        cout << endl ;


        for( int i = 0 ; i < r ; i+=2 )
            if(ck[i] == ck[i+1] )
            {
                Ans = 0;
                break ;
            }
        if(Ans == 1 )
        {
            //cout << "sigh" << endl ;
            graph_compression();
          //  cout << "sigh" << endl ;
            memset(ck,0,sizeof(ck)) ;
            memset(up,0,sizeof(up)) ;
//            for( int i = 1 ; i <= cnt ; i++ )
//            {
//                for( int j = 0 ; j < graph[i].size() ; j++ )
//                    cout << graph[i][j] << " " ;
//                cout << endl ;
//            }

            for(int i = 1 ; i <= cnt ; i++) theLastCalc(i) ;
            for( int i = 1 ; i <= m ; i++ ) if(s[i] == 1 )ans.push_back(i);
        }



        printf("Case %d: ",cs ) ;
        if(!Ans)printf("No") ;
        else
        {
            printf("Yes\n%d", ans.size()) ;
            for(int i = 0 ; i < ans.size(); i++)printf(" %d", ans[i] ) ;
        }
        printf("\n");
    }



    return 0 ;
}
