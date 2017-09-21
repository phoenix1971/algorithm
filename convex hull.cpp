#include <bits/stdc++.h>
using namespace std;

typedef double ll ;
typedef long long coord_t;         // coordinate type
typedef long long coord2_t;  // must be big enough to hold 2*max(|coordinate|)^2
typedef pair<ll,ll> pdd ;
#define xx first
#define yy second

struct Point
{
    coord_t x, y;

    bool operator <(const Point &p) const
    {
        return x < p.x || (x == p.x && y < p.y);
    }
    void print()
    {
        cout << "point " << x << " " << y << endl ;
    }
};

// 2D cross product of OA and OB vectors, i.e. z-component of their 3D cross product.
// Returns a positive value, if OAB makes a counter-clockwise turn,
// negative for clockwise turn, and zero if the points are collinear.
coord2_t cross(const Point &O, const Point &A, const Point &B)
{
    return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

// Returns a list of points on the convex hull in counter-clockwise order.
// Note: the last point in the returned list is the same as the first one.
vector<Point> convex_hull(vector<Point> P)
{
    int n = P.size(), k = 0;
    if (n == 1) return P;
    vector<Point> H(2*n);

    // Sort points lexicographically
    sort(P.begin(), P.end());

    // Build lower hull
    for (int i = 0; i < n; ++i)
    {
        while (k >= 2 && cross(H[k-2], H[k-1], P[i]) <= 0) k--;
        H[k++] = P[i];
    }

    // Build upper hull
    for (int i = n-2, t = k+1; i >= 0; i--)
    {
        while (k >= t && cross(H[k-2], H[k-1], P[i]) <= 0) k--;
        H[k++] = P[i];
    }

    H.resize(k-1);
    return H;
}

ll AREA(Point A, Point B, Point C)
{
    ll area =  ( A.x*B.y - B.x*A.y + B.x*C.y - B.y*C.x - A.x*C.y + A.y * C.x ) ;
    area = abs(area) ;
    return area ;
}

int n  ;
vector<Point>P,np ;
Point p ;
ll s ,x,y ;



int main()
{
    //sigh() ;
    cin >> n >> s ;
    for(int i = 0 ; i < n ; i++ )
    {
        scanf("%lf %lf",&x,&y);
        p.x = x , p.y = y ;
        P.push_back(p) ;
    }
    np = convex_hull(P) ;
    n = np.size() ;


    return 0 ;
}
