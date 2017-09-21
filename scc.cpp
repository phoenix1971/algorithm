#include <bits/stdc++.h>
using namespace std ;
typedef unsigned int ui ;

int cs , t ;
int ck[10004] , oy[10004] , ans , in[10004] ;
vector < int > bro[10004] , orb[10004] , scc[10004] ;
stack < int > yo ;
void go(int u )
{
    if(ck[u]== 1 ) return ;
    ck[u] = 1 ;

    for(int i = 0 ; i < bro[u].size() ; i++ )
        go(bro[u][i]) ;

    yo.push(u) ;
}

void go(int u , int bap )
{
    if( ck[u] == 2 ) return ;
    ck[u] = 2 ;
    oy[u] = bap ;
    scc[bap].push_back(u) ;
   // cout << u << " " ;
    for(int i = 0 ; i < orb[u].size() ; i++ )
        go(orb[u][i],bap)  ;
}


int main()
{
    cin >> t ;

    while( cs < t )
    {
        cs++ ;
        memset(ck,0,sizeof(ck));
        //memset(oy,0,sizeof(oy));
        for(int i = 1 ; i <= 10000 ; i++ ) oy[i] = i ;
        memset(in,0,sizeof(in));
        while( !yo.empty())yo.pop();
        ans = 0 ;
        for( int i = 0 ; i < 10004;i++)bro[i].clear(),orb[i].clear();
        int n , m , x, y ;
        scanf("%d %d", &n, &m ) ;
        for( int i = 0 ; i < m ; i++)
        {
            scanf("%d %d", &x, &y );
            bro[x].push_back(y);
            orb[y].push_back(x);
        }
        for( int i = 1 ; i <= n ; i++ )
            if(ck[i] != 1 ) go(i) ;

        while( !yo.empty())
        {
            int u = yo.top();
            yo.pop() ;
            if(ck[u] != 2 )
            {
                go(u,u);
                //cout << endl << endl  ;
            }
        }
        for( int u = 1 ; u <= n ; u++ )
        {
            printf("scc of %d : ", u ) ;
            for( int i = 0 ; i < scc[u].size() ; i++ )
            {
                printf("%d ", scc[u][i] ) ;
            }
            printf("\n");
        }



    }



    return 0 ;
 }
/*


1
8 12
1 2
2 3
3 1
4 5
5 4
1 4
3 5
6 7
7 8
8 6
4 6
5 8



*/
