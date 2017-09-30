#include <stdio.h>
#include <bits/stdtr1c++.h>

#define MAXP 100000
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl
#define ran(a, b) ((((rand() << 15) ^ rand()) % ((b) - (a) + 1)) + (a))

using namespace std;


struct crt{
    long long extended_gcd(long long a, long long b, long long& x, long long& y){
        if (!b){
            y = 0, x = 1;
            return a;
        }

        long long g = extended_gcd(b, a % b, y, x);
        y -= ((a / b) * x);
        return g;
    }

    long long mod_inverse(long long a, long long m){
        long long x, y;
        extended_gcd(a, m, x, y);
        return (x + m) % m;
    }

    long long chinese_remainder(vector <long long> ar, vector <long long> mods){
        long long x, y, res = 0, M = 1;
        for (int i = 0; i < ar.size(); i++) M *= mods[i];
        for (int i = 0; i < ar.size(); i++){
            x = M / mods[i], y = mod_inverse(x, mods[i]);
            res = (res + (((x * ar[i]) % M) * y)) % M;
        }
        return res;
    }

    long long mod = 0, dp[MAXP];

    long long trailing(long long x, long long p){
        long long res = 0;
        while (x){
            x /= p;
            res += x;
        }
        return res;
    }

    long long expo(long long a, long long b, long long m){
        long long res = 1;

        while (b){
            if (b & 1) res = res * a % m;
            a = a * a % m, b >>= 1;
        }
        return res;
    }

    long long factorial(long long x, long long p){
        long long res = expo(dp[mod - 1], x / mod, mod);
        if (x >= p) res = res * factorial(x / p, p) % mod;
        return res * dp[x % mod] % mod;
    }

    long long binomial(long long n, long long k, long long p, long long q){
        if (k > n || k < 0) return 0;
        if (n == k || k == 0) return 1;

        int i, j;
        for (i = 0, mod = 1; i < q; i++) mod *= p;
        long long t = trailing(n, p) - trailing(k, p) - trailing(n - k, p);
        if (t >= q) return 0;

        assert(mod < MAXP);
        for (dp[0] = 1, i = 1; i < mod; i++){
            dp[i] = (long long)dp[i - 1] * ((i % p) ? i : 1) % mod;
        }

        long long res = factorial(n, p) * expo(factorial(k, p) * factorial(n - k, p) % mod, (mod / p) * (p - 1) - 1, mod) % mod;
        for (i = 0; i < t; i++) res = res * p % mod;
        return res;
    }

    long long binomial(long long n, long long k, long long m){
        if (k > n || m == 1 || k < 0) return 0;
        if (n == k || k == 0) return 1;

        vector <pair<int, int> > factors;
        for (long long i = 2; i * i <= m; i++){
            int c = 0;
            while (m % i == 0){
                c++;
                m /= i;
            }
            if (c) factors.push_back(make_pair(i, c));
        }
        if (m > 1) factors.push_back(make_pair(m, 1));

        vector <long long> ar, mods;
        for (int i = 0; i < factors.size(); i++){
            long long x = 1;
            for (int j = 0; j < factors[i].second; j++) x *= factors[i].first;
            mods.push_back(x), ar.push_back(binomial(n, k, factors[i].first, factors[i].second));
        }
        return chinese_remainder(ar, mods);
    }
    long long NCR(long long n, long long k, long long MOD )
    {
        return binomial(n, k, MOD);
    }
};



long long bigMOD(long long x,long long n , long long mod)
{
    //cout << x << " " << n << " " << mod << endl ;
    if(n==0)return 1;
    long long ret = bigMOD(x,n/2,mod);
    ret *= ret ;
    ret %= mod ;
    if(n%2==1)ret *= x , ret %= mod ;
    //cout << "ret = " << ret << endl ;
    return ret ;
}
crt Crt ;
int main(){

    long long n, k ,l , m ;
    int t , cs ;
    cin>>t;
    while (cs<t)
    {
        cs++;

        scanf("%lld %lld %lld %lld",&n,&k,&l,&m);
        long long ans ;
        if(k==1)
        {
            if(m==0)ans=1;
            else ans = 0;
        }
        else
        {
            ans = Crt.NCR(l,m,n);
            //cout << ": " << ans << endl ;
            ans *= bigMOD(k,l-m,n) ;
            ans %= n ;
            //cout << ": " << ans << endl ;
            if(m>0)ans *= (k*(k-1)/2)%n ;
            ans %= n ;
            //cout << ": " << ans << " " << n << endl ;
            if(m>0)ans *= bigMOD((k*(k-1))%n,m-1,n) , ans %= n ;
            //cout << ": " << ans << endl ;
        }
        //cout << 1+ans << endl ;
        ans++;
        printf("Case %d: %lld\n",cs,ans);
    }
    return 0;
}
