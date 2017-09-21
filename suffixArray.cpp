/************************************************************************
    Suffix Array. Builing works in O(NlogN).
    Also LCP array is calculated in O(NlogN).
    This code counts number of different substrings in the string.
    Based on problem I from here: http://codeforces.ru/gym/100133
************************************************************************/

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 205000;
const int ALPH = 256;
const int MAXLOG = 20;

int n;
string s ;
int p[MAXN]; // suffix array itself
int pcur[MAXN];
int c[MAXN][MAXLOG];
int num[MAXN];
int classesNum;
int lcp[MAXN];

void clr()
{
    memset(p,0,sizeof(p));
    memset(pcur,0,sizeof(pcur));
    memset(c,0,sizeof(c));
    memset(num,0,sizeof(num));
    memset(lcp,0,sizeof(lcp));
}

void buildSuffixArray() {
    n++;

    for (int i = 0; i < n; i++)
        num[s[i]]++;

    for (int i = 1; i < ALPH; i++)
        num[i] += num[i - 1];

    for (int i = 0; i < n; i++) {
        p[num[s[i]] - 1] = i;
        num[s[i]]--;
    }

    c[p[0]][0] = 1;
    classesNum = 1;
    for (int i = 1; i < n; i++) {
        if (s[p[i]] != s[p[i - 1]])
            classesNum++;
        c[p[i]][0] = classesNum;
    }

    for (int i = 1; ; i++) {

        int half = (1 << (i - 1));

        for (int j = 0; j < n; j++) {
            pcur[j] = p[j] - half;
            if (pcur[j] < 0)
                pcur[j] += n;
        }

        for (int j = 1; j <= classesNum; j++)
            num[j] = 0;

        for (int j = 0; j < n; j++)
            num[c[pcur[j]][i - 1]]++;
        for (int j = 2; j <= classesNum; j++)
            num[j] += num[j - 1];

        for (int j = n - 1; j >= 0; j--) {
            p[num[c[pcur[j]][i - 1]] - 1] = pcur[j];
            num[c[pcur[j]][i - 1]]--;
        }

        c[p[0]][i] = 1;
        classesNum = 1;

        for (int j = 1; j < n; j++) {
            int p1 = (p[j] + half) % n, p2 = (p[j - 1] + half) % n;
            if (c[p[j]][i - 1] != c[p[j - 1]][i - 1] || c[p1][i - 1] != c[p2][i - 1])
                classesNum++;
            c[p[j]][i] = classesNum;
        }

        if ((1 << i) >= n)
            break;
    }

    for (int i = 0; i < n; i++)
        p[i] = p[i + 1];
    n--;
}

int getLcp(int a, int b) {
    int res = 0;
    for (int i = MAXLOG - 1; i >= 0; i--) {
        int curlen = (1 << i);
        if (curlen > n)
            continue;
        if (c[a][i] == c[b][i]) {
            res += curlen;
            a += curlen;
            b += curlen;
        }
    }
    return res;
}

void calcLcpArray() {
    for (int i = 0; i < n - 1; i++)
        lcp[i] = getLcp(p[i], p[i + 1]);
}
string sa, sb, sc ;
int id[20000] ;

int solve() {
    clr() ;
    memset(id,0,sizeof(id));
    cin>>sa>>sb>>sc ;
    s = sa + "." + sb + "." + sc ;
    n = s.size() ;

    buildSuffixArray();

    // Now p from 0 to n - 1 contains suffix array of original string
    for (int i = 0; i < n; i++) {
        //printf("%d ", p[i] + 1);
        if(p[i] < sa.size() )id[i] = 0 ;
        else if( p[i] >sa.size() && p[i] < sa.size()+sb.size()+1)id[i] = 1 ;
        else id[i] = 2 ;
    }
    //cout << endl ;
    calcLcpArray();
    int ans = 0 ;
    for (int i = 0; i < n-2 ; i++) {
        //printf("%d %d %d\n", p[i]+1 , lcp[i] , id[i] );
        if(id[i]!= id[i+1] && id[i+1] != id[i+2] && id[i] != id[i+2] )ans = max ( ans, min(lcp[i],lcp[i+1])) ;
    }
    return ans ;
}

int main() {
//    assert(freopen("substr.in","r",stdin));
//    assert(freopen("substr.out","w",stdout));

    int t , cs = 0 ;
    cin>>t;
    while(cs<t)
    {
        cs++ ;
        printf("Case %d: %d\n",cs, solve() ) ;
    }


    return 0;
}
