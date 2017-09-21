#include <bits/stdc++.h>
using namespace std ;

struct Tree {

    Tree *l , *r  ;
    Tree()
    {
        //cout << "sigh" << endl ;
        l = r  = NULL ;
    }
    Tree( Tree* L , Tree *R )
    {
        l = L ;
        r = R ;
    }


};



Tree *root[300005] ;

int n, q ;
int r, e[300005], x ;
vector < int > bro[100005] ;
int lastAns ;
int last ;

Tree * insrt( Tree* old , int x , int b )
{
    //cout << x << " " << b << endl ;
    Tree *notun = new Tree(old->l , old->r ) ;
    //cout << "yo " << endl ;
    if(b == 0 )
    {
        if((x&1)== 0 )
        {
            if(notun->l == NULL ) notun->l = new Tree() ;
        }
        else
        {
            if(notun->r == NULL ) notun->r = new Tree() ;
        }
    }
    else
    {
        if((x&(1<<b))== 0 )
        {
            if(notun->l == NULL ) notun->l = new Tree() ;
            notun->l = insrt(notun->l,x,b-1 ) ;
        }
        else
        {
            if(notun->r == NULL ) notun->r = new Tree() ;
            notun->r = insrt(notun->r,x,b-1 ) ;
        }

    }
    return notun ;

}
void in( int u, int p, int k ) {

  //  cout << u << " " <<p << " " << k << endl ;
    root[u] = insrt(root[p] , k , 31 ) ;
}

int calc( int u , int k )
{
    int ans = 0 ;
    Tree *node = root[u] ;

    for( int i = 31 ; i > -1 ; i-- )
    {
        int id = ( k & ( 1 << i ) ) ;

        if( id == 0 )
        {
            if( node->l != NULL ) node = node->l ;
            else node= node->r , ans = ( ans | ( 1 << i ) ) ;//, cout << "i = " << i << "  && id = "<< 0 << endl ;
        }
        else
        {
            if( node->r != NULL ) node= node->r , ans = ( ans | ( 1 << i ) );
            else  node = node->l ;// cout << "i = " << i << " && id = "<< 1 << endl ;
        }

    }
    return ans ;
}
int dfs( int u, int par ) {

  //  cout << u << " " << par << endl ;
    in( u, par, e[u] ) ;

    for( int i = 0 ; i < bro[u].size() ; i++ ) {
        dfs(bro[u][i], u  ) ;

    }
}


int main() {


    int u, v, w ;

    cin >> n >> q ;
    cin >> r >> x ;
    e[r] = x ;

    for( int i = 1 ; i < n ; i++ ) {
        scanf("%d %d %d",&u,&v,&w) ;
        bro[v].push_back(u) ;
        e[u] = w ;
    }
    root[0] = new Tree() ;
    dfs(r,0  );

    int type, k ;
    for( int i = 0 ; i < q ; i++ ) {
        scanf("%d",&type );
        type ^= lastAns ;
        if( type == 0 ) {
            scanf("%d %d %d",&v,&u,&k) ;
            v ^= lastAns ;
            u ^= lastAns ;
            k ^= lastAns ;
            in(u,v,k) ;
        }
        else {
            scanf("%d %d",&v,&k) ;
            v ^= lastAns ;
            k ^= lastAns ;
           // cout <<"sigh 1 k = "<< k << endl ;
            int mn = calc(v,k) ^ k ;
          //  cout <<"sigh 2 "<< endl ;
            int mx = calc(v,~k) ^ k ;

             printf("%d %d\n", mn , mx ) ;
             lastAns = mn ^ mx ;
        }
    }


    return 0 ;
}

/*

3 10
1 2
2 1 3
3 2 4


7 3
1 2
5 1 3
2 1 4
3 2 5
4 2 1
6 3 3
10 6 6
1 4 2
7 12 7
4 0 7


6 4
1 2
5 1 3
2 1 4
3 2 5
4 2 1
6 3 3
1 4 2
6 0 12 0
7 12 7
4 0 7

*/
