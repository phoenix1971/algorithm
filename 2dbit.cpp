using namespace std;

const int MAXN = 1050;

int n, m;
int qn;
char q[10];
int f[MAXN][MAXN];

void update(int x, int y, int delta) {
    for (int i = x; i <= n; i = i | (i + 1))
        for (int j = y; j <= m; j = j | (j + 1))
            f[i][j] += delta;
}

int getSum(int x, int y) {
    int res = 0;
    for (int i = x; i > 0; i = (i & (i + 1)) - 1)
        for (int j = y; j > 0; j = (j & (j + 1)) - 1)
            res += f[i][j];
    return res;
}

int getSum(int xFrom, int xTo, int yFrom, int yTo) {
    return getSum(xTo, yTo) - getSum(xTo, yFrom - 1) - getSum(xFrom - 1, yTo) + getSum(xFrom - 1, yFrom - 1);
}

int main() {
    //assert(freopen("input.txt","r",stdin));
    //assert(freopen("output.txt","w",stdout));

    scanf("%d %d\n", &n, &qn);
    m = n;

    for (int i = 1; i <= qn; i++) {
        scanf("%s", &q);
        if (q[0] == 'A') {
            int x, y;
            scanf("%d %d\n", &x, &y);
            update(x, y, 1);
        }
        else {
            int xFrom, xTo, yFrom, yTo;
            scanf("%d %d %d %d\n", &xFrom, &yFrom, &xTo, &yTo);
            if (xFrom > xTo)
                swap(xFrom, xTo);
            if (yFrom > yTo)
                swap(yFrom, yTo);
            printf("%d\n", getSum(xFrom, xTo, yFrom, yTo));
        }
    }

    return 0;
}
