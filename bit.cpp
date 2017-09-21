#include <bits/stdc++.h>
using namespace std ;

int tree[100005] ;
const int n = 100000 ;
int query(int idx){
       int sum=0;
       while(idx>0){
             sum+=tree[idx];
             idx -= idx & (-idx);
       }
       return sum;
}

void update(int idx, int x) //n is the size of the array, x is the number to add
{
       while(idx<=n)
       {
             tree[idx]+=x;
             idx += idx & (-idx);
       }
}

int rangeQuery( int l , int r )
{
    return query(r)-query(l-1) ;
}

int main()
{



return 0 ;
}
