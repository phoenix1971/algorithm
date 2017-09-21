#include <bits/stdc++.h>
using namespace std ;

/*
 * Implicit Treap
 * all the index is 1 based
 */
struct NODE{
    int Value,Prior,Cnt;
    bool Rev;
    NODE *l, *r;
    NODE( int Value = 0,int Prior = 0 ):Value( Value ),Prior( Prior ),Cnt(1),Rev( false ), l( NULL ), r( NULL ){}
};

typedef NODE* P_NODE;

class TREAP{
    P_NODE Root;
    vector<NODE> Pool;
    int PoolPointer;

    P_NODE Create( int Value,int Prior = rand( ) ){
        P_NODE ret = &Pool[PoolPointer++];
        *ret = NODE( Value,Prior );
        return ret;
    }
    int Count( P_NODE t ){
        return t ? t->Cnt: 0;
    }
    /* Lazy to reverse the child */
    void Push( P_NODE t ){
        if( t && t->Rev ){
            t->Rev = false;
            swap( t->l ,t->r );
            if( t->l ) t->l->Rev ^= true;
            if( t->r ) t->r->Rev ^= true;
        }
    }
    void Update( P_NODE t ){
        if( t ){
            Push( t );
            t->Cnt = 1 + Count(t->l ) + Count(t->r );
        }
    }
    void Split( P_NODE t, int Pos, P_NODE &l, P_NODE &r ,int Add = 0 ){
        if( !t ) return void( l = r = NULL );
        Push( t );
        int Cur_Pos = Add + Count( t->l ) + 1;
        if( Pos <= Cur_Pos ) Split( t->l, Pos, l, t->l,Add ), r = t;
        else Split( t->r, Pos, t->r, r , Add + 1 + Count( t->l ) ), l = t;
        Update( t );
    }
    void Merge( P_NODE &t, P_NODE l, P_NODE r ){
        Push( l ),Push( r );
        if( !l or !r ) t = l?l:r;
        else if( l->Prior > r->Prior ) Merge(l->r, l->r, r ), t = l;
        else Merge(r->l, l, r->l ), t = r;
        Update( t );
    }
    void Insert( P_NODE &t, P_NODE it ,int Pos ){
        if( !t ) return void( t = it );
        P_NODE l,r;
        Split( t,Pos, l, r );
        Merge( t,l,it );
        Merge( t,t,r );
        Update( t );
    }
    void Erase( P_NODE &t, int Pos ,int Add = 0 ){
        if( !t ) return;
        P_NODE l,r;
        Split( t,Pos,l,t );
        Split( t,2,t,r );
        Merge( t,l,r );
        Update( t );
    }
    void Output( P_NODE t ){
        if( !t ) return;
        Push( t );
        Output( t->l );
        printf("%ld\n",t->Value );
        Output( t->r );
    }
public:
    TREAP( int PoolSize ) : Root( NULL ), PoolPointer( 0 ){
        srand(time(NULL ) );
        Pool.resize( PoolSize );
    }
    /* Count tot number of node */
    int COUNT( ){
        return Count( Root );
    }
    /* Insert a value in a Pos th position */
    void INSERT( int Pos,int Value ){
        Insert( Root,Create( Value ),Pos );
    }
    /* Erase node from pos */
    void ERASE( int Pos ){
        Erase( Root,Pos );
    }
    /* Reverse a range l -> r */
    void REVERSE( int l, int r){
        P_NODE t1,t2,t3;
        Split( Root,l,t1,t2 );
        Split( t2,(r-l+1)+1,t2,t3 );
        t2->Rev ^= true;
        Merge( Root,t1,t3 );
        Merge( Root,Root,t2 );
    }
    void OUTPUT( void ){
        Output( Root );
    }
};


TREAP treap(100005) ;

int main()
{
    int n ,q,l,r;
    cin>>n>>q;
    for(int i = 1 ; i <= n ; i++)
    {
        treap.INSERT(i,i) ;
    }
    for(int i = 0 ; i < q ; i++)
    {
        scanf("%d %d",&l,&r);
        treap.REVERSE(l,r) ;
    }
    treap.OUTPUT() ;



return 0 ;
}
