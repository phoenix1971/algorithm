#include <bits/stdc++.h>
using namespace std ;

double INF = 1e6;
double EPS = 1e-9;

struct PT {
  double x, y;
  PT() {}
  PT(double x, double y) : x(x), y(y) {}
  PT(const PT &p) : x(p.x), y(p.y)    {}
  PT operator + (const PT &p)  const { return PT(x+p.x, y+p.y); }
  PT operator - (const PT &p)  const { return PT(x-p.x, y-p.y); }
  PT operator * (double c)     const { return PT(x*c,   y*c  ); }
  PT operator / (double c)     const { return PT(x/c,   y/c  ); }
};

double dot(PT p, PT q)     { return p.x*q.x+p.y*q.y; }
double dist2(PT p, PT q)   { return dot(p-q,p-q); }
double dist(PT p, PT q)   { return sqrt(dist2(p,q)); }
double cross(PT p, PT q)   { return p.x*q.y-p.y*q.x; }
ostream &operator<<(ostream &os, const PT &p) {
  os << "(" << p.x << "," << p.y << ")";
}

// rotate a point CCW or CW around the origin
PT RotateCCW90(PT p)   { return PT(-p.y,p.x); }
PT RotateCW90(PT p)    { return PT(p.y,-p.x); }
PT RotateCCW(PT p, double t) {
  return PT(p.x*cos(t)-p.y*sin(t), p.x*sin(t)+p.y*cos(t));
}

// project point c onto line through a and b
// assuming a != b
PT ProjectPointLine(PT a, PT b, PT c) {
  return a + (b-a)*dot(c-a, b-a)/dot(b-a, b-a);
}

// project point c onto line segment through a and b
PT ProjectPointSegment(PT a, PT b, PT c) {
  double r = dot(b-a,b-a);
  if (fabs(r) < EPS) return a;
  r = dot(c-a, b-a)/r;
  if (r < 0) return a;
  if (r > 1) return b;
  return a + (b-a)*r;
}

// compute distance from c to segment between a and b
double DistancePointSegment(PT a, PT b, PT c) {
  return sqrt(dist2(c, ProjectPointSegment(a, b, c)));
}
double DistancePointLine(PT a,  PT b , PT c)
{
    PT t1 = a - ( b - a )*INF ;
    PT t2 = a + ( b - a )*INF ;
    //cout << "t " <<t1 << " " <<t2 << endl ;
    return DistancePointSegment(t1,t2,c);
}
// compute distance between point (x,y,z) and plane ax+by+cz=d
double DistancePointPlane(double x, double y, double z,
                          double a, double b, double c, double d)
{
  return fabs(a*x+b*y+c*z-d)/sqrt(a*a+b*b+c*c);
}

// determine if lines from a to b and c to d are parallel or collinear
bool LinesParallel(PT a, PT b, PT c, PT d) {
  return fabs(cross(b-a, c-d)) < EPS;
}

bool LinesCollinear(PT a, PT b, PT c, PT d) {
  return LinesParallel(a, b, c, d)
      && fabs(cross(a-b, a-c)) < EPS
      && fabs(cross(c-d, c-a)) < EPS;
}

// determine if line segment from a to b intersects with
// line segment from c to d
bool SegmentsIntersect(PT a, PT b, PT c, PT d) {
  if (LinesCollinear(a, b, c, d)) {
    if (dist2(a, c) < EPS || dist2(a, d) < EPS ||
      dist2(b, c) < EPS || dist2(b, d) < EPS) return true;
    if (dot(c-a, c-b) > 0 && dot(d-a, d-b) > 0 && dot(c-b, d-b) > 0)
      return false;
    return true;
  }
  if (cross(d-a, b-a) * cross(c-a, b-a) > 0) return false;
  if (cross(a-c, d-c) * cross(b-c, d-c) > 0) return false;
  return true;
}
bool lineIntersect(PT a, PT b, PT c, PT d)
{
    PT ab = b - a ;
    PT cd = d - c ;
    return (abs(cross(ab,cd)) > 0.00 );
}
bool lineSegIntersect(PT a, PT b, PT c, PT d )
{
    PT t1 = a - ( b - a )*INF ;
    PT t2 = a + ( b - a )*INF ;
    return SegmentsIntersect(t1,t2,c,d) ;
}
PT o ;
double distanceBetweenLine(PT a, PT b, PT c,PT d)
{
    double c1 = DistancePointLine(a,b,o);
    double c2 = DistancePointLine(c,d,o);
    //cout << "c " << c1 << " " << c2 << endl ;
    bool v1 = a.x*(a.y-b.y) > a.y*(a.x-b.x);
    bool v2 = c.x*(c.y-d.y) > d.y*(c.x-d.x);
    //cout << "v = " << v1 << " " <<v2 << endl;
    if(v1==v2)return abs(c1-c2);
    else return abs(c1+c2);

}
double findDis(PT a, PT b, PT c)
{
    double lo = 0.00 , hi = dist(a,b) ;
    int cnt = 0 ;
    while(cnt<200&&abs(hi-lo)>EPS)
    {
        cnt++ ;
        double ml = (2*lo+hi)/3.00 ;
        double mh = (lo+2*hi)/3.00 ;
        double dl = dist(c,a+(b-a)/sqrt(dot(b-a,b-a))*ml);
        double dh = dist(c,a+(b-a)/sqrt(dot(b-a,b-a))*mh);
        if(dl<dh)hi = mh ;
        else lo = ml ;
    }
    return dist(c,a+(b-a)/sqrt(dot(b-a,b-a))*lo) ;
}
const double error = 2e-5 ;
PT a , b , c, d , yo , oy ;
string ta , tc ;
int main()
{
//    freopen("in.txt","r",stdin ) ;
//    freopen("out.txt","w",stdout ) ;
o.x = 0.00 , o.y = 0.00 ;
yo.x = yo.y = oy.y = 1 ;
oy.x = 2 ;
//printf("%0.9lf\n",error);
while(true)
{
    scanf("%lf %lf %lf %lf",&a.x,&a.y,&b.x,&b.y);
    cin>>ta ;
    scanf("%lf %lf %lf %lf",&c.x,&c.y,&d.x,&d.y);
    cin>>tc ;
    if(ta=="END"){break;}
    if(ta=="L"&&tc=="L")
    {
        if(lineIntersect(a,b,c,d))printf("0.00000\n");
        else
        {
            printf("%0.5lf\n", distanceBetweenLine(a,b,c,d)) ;
        }
    }
    else if(ta=="L")
    {
        if(!lineIntersect(a,b,c,d))printf("%0.5lf\n", distanceBetweenLine(a,b,c,d)) ;
        else if(lineSegIntersect(a,b,c,d))printf("0.00000\n");
        else
        {
            printf("%0.5lf\n",min(DistancePointLine(a,b,c),DistancePointLine(a,b,d) ));
        }
    }
    else if(tc=="L")
    {
        if(!lineIntersect(a,b,c,d))printf("%0.5lf\n", distanceBetweenLine(a,b,c,d)) ;
        else if(lineSegIntersect(c,d,a,b))printf("0.00000\n");
        else
        {
            printf("%0.5lf\n",min(DistancePointLine(c,d,a),DistancePointLine(c,d,b) ));
        }
    }
    else
    {
        double lo = 0.00 ;
        double hi = dist(a,b) ;
        int cnt = 0 ;
        while(cnt<200&&abs(hi-lo)>EPS)
        {
            cnt++ ;
            double ml = (2*lo+hi)/3.00 ;
            double mh = (lo+2*hi)/3.00 ;
            double dl = findDis(c,d,a+(b-a)/sqrt(dot(b-a,b-a))*ml);
            double dh = findDis(c,d,a+(b-a)/sqrt(dot(b-a,b-a))*mh);
            if(dl<dh)hi = mh ;
            else lo = ml ;
        }
        printf("%0.5lf\n",findDis(c,d,a+(b-a)/sqrt(dot(b-a,b-a))*lo));
    }
}

return 0 ;
}
