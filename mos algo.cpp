#include <bits/stdc++.h>
using namespace std ;
int sqt;
int a[100005] ;
int cnt[100005] , res[100005] ;
int ans ;

struct el
{
    int l, r, in;
};

bool cmp(const el &x, const el &y)
{
    if (x.l/sqt != y.l/sqt)
        return x.l/sqt < y.l/sqt;
    return x.r < y.r;
}

el qr[200005];

int main()
{

    int n, q, a, b;
    cin >> n >> q;
    sqt = sqrt((double)(n))+1;
    for (int i = 0; i < n; i++)scanf("%d",&a[i]) ;
    for (int i = 0; i < q; i++)
    {
        scanf("%d %d",&a,&b);
        a--; b--;
        qr[i].l = a;
        qr[i].r = b;
        qr[i].in = i;
    }
    sort(qr, qr+q, cmp);
    int li = 0;
    int ri = 0;
    ans = 1 ;
    cnt[a[0]]++;

    for (int i = 0; i < q; i++)
    {
        while (li < qr[i].l)
        {
            ans -= cnt[arr[li]]*cnt[arr[li]]*arr[li];
            cnt[arr[li]]--;
            ans += cnt[arr[li]]*cnt[arr[li]]*arr[li];
            li++;
        }
        while (li > qr[i].l)
        {
            li--;
            ans -= cnt[arr[li]]*cnt[arr[li]]*arr[li];
            cnt[arr[li]]++;
            ans += cnt[arr[li]]*cnt[arr[li]]*arr[li];
        }
        while (ri < qr[i].r)
        {
            ri++;
            ans -= cnt[arr[ri]]*cnt[arr[ri]]*arr[ri];
            cnt[arr[ri]]++;
            ans += cnt[arr[ri]]*cnt[arr[ri]]*arr[ri];
        }
        while (ri > qr[i].r)
        {
            ans -= cnt[arr[ri]]*cnt[arr[ri]]*arr[ri];
            cnt[arr[ri]]--;
            ans += cnt[arr[ri]]*cnt[arr[ri]]*arr[ri];
            ri--;
        }
        res[qr[i].in] = ans;
    }
    for (int i = 0; i < q; i++)
        printf("%d\n",res[i] ) ;
}
