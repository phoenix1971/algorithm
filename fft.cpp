#include<bits/stdc++.h>
using namespace std;

typedef long long ll ;
typedef vector<ll> VI;
double PI = acos(0) * 2;

class _complex
{
public:
	double a, b;
	_complex() {a = 0.0; b = 0.0;}
	_complex(double na, double nb) {a = na; b = nb;}
	const _complex operator+(const _complex &c) const
		{return _complex(a + c.a, b + c.b);}
	const _complex operator-(const _complex &c) const
		{return _complex(a - c.a, b - c.b);}
	const _complex operator*(const _complex &c) const
		{return _complex(a*c.a - b*c.b, a*c.b + b*c.a);}
	double magnitude() {return sqrt(a*a+b*b);}
	void print() {printf("(%.3f %.3f)\n", a, b);}
};

class FFT
{
public:
	vector<_complex> data;
	vector<_complex> roots;
	VI rev;
	ll s, n;

	void setSize(ll ns)
	{
		s = ns;
		n = (1 << s);
		ll i, j;
		rev = VI(n);
		data = vector<_complex> (n);
		roots = vector<_complex> (n+1);
		for (i = 0; i < n; i++)
			for (j = 0; j < s; j++)
				if ((i & (1 << j)) != 0)
					rev[i] += (1 << (s-j-1));
		roots[0] = _complex(1, 0);
		_complex mult = _complex(cos(2*PI/n), sin(2*PI/n));
		for (i = 1; i <= n; i++)
			roots[i] = roots[i-1] * mult;
	}

	void bitReverse(vector<_complex> &array)
	{
		vector<_complex> temp(n);
		ll i;
		for (i = 0; i < n; i++)
			temp[i] = array[rev[i]];
		for (i = 0; i < n; i++)
			array[i] = temp[i];
	}

	void transform(bool inverse = false)
	{
		bitReverse(data);
		ll i, j, k;
		for (i = 1; i <= s; i++) {
			ll m = (1 << i), md2 = m / 2;
			ll start = 0, increment = (1 << (s-i));
			if (inverse) {
				start = n;
				increment *= -1;
			}
			_complex t, u;
			for (k = 0; k < n; k += m) {
				ll index = start;
				for (j = k; j < md2+k; j++) {
					t = roots[index] * data[j+md2];
					index += increment;
					data[j+md2] = data[j] - t;
					data[j] = data[j] + t;
				}
			}
		}
		if (inverse)
			for (i = 0; i < n; i++) {
				data[i].a /= n;
				data[i].b /= n;
			}
	}

	static VI convolution(VI &a, VI &b)
	{
		ll alen = a.size(), blen = b.size();
		ll resn = alen + blen - 1;	// size of the resulting array
		ll s = 0, i;
		while ((1 << s) < resn) s++;	// n = 2^s
		ll n = 1 << s;	// round up the the nearest power of two

		FFT pga, pgb;
		pga.setSize(s);	// fill and transform first array
		for (i = 0; i < alen; i++) pga.data[i] = _complex(a[i], 0);
		for (i = alen; i < n; i++)	pga.data[i] = _complex(0, 0);
		pga.transform();

		pgb.setSize(s);	// fill and transform second array
		for (i = 0; i < blen; i++)	pgb.data[i] = _complex(b[i], 0);
		for (i = blen; i < n; i++)	pgb.data[i] = _complex(0, 0);
		pgb.transform();

		for (i = 0; i < n; i++)	pga.data[i] = pga.data[i] * pgb.data[i];
		pga.transform(true);	// inverse transform
		VI result = VI (resn);	// round to nearest integer
		for (i = 0; i < resn; i++)	result[i] = (ll) (pga.data[i].a + 0.5);

		ll actualSize = resn - 1;	// find proper size of array
		while (result[actualSize] == 0)
			actualSize--;
		if (actualSize < 0) actualSize = 0;
		result.resize(actualSize+1);
		return result;
	}
};

int main()
{
	VI a ;
	for (int i = 0; i < 10; i++)a.push_back(1) ;
	VI b = FFT::convolution(a, a);
	/* 1 8 34 104 259 560 1092 1968 3333
	5368 8052 11120 14259 17104 19234 20168 19361 16200 10000*/
	for (int i = 0; i < b.size(); i++)
		printf("%lld ", b[i]);
	return 0;
}
//VL a , b, res ;
//
//ll NC( ll x)
//{
//    return x * (x-1) * (x-2) / 6 ;
//}
//int main()
//{
//
//    cin>>n ;
//    for(int i = 0 ; i < n ; i++ )
//    {
//        scanf("%lld",&x);
//        cnt[x]++ ;
//    }
//    for( int i = 1 ; i <= 30000 ; i++ )
//    {
//        a.push_back(cnt[i]);
//        b.push_back(cnt[i]);
//    }
//    Multiply(a,b,res);
//    ll ans = 0 ;
//    cout << res.size() << endl ;
//    for(int i = 2 ; i < 20 ; i+=2 )
//    {
//        printf("%lld\n", res[i] ) ;
//        ans += ( res[i] - cnt[i/2]*cnt[i/2] )*cnt[i/2] ;
//    }
//    for( int i = 1 ; i <= 30000 ; i++ )
//    {
//        ans += NC(cnt[i] ) ;
//    }
//    cout << ans ;
//return 0 ;
//}
