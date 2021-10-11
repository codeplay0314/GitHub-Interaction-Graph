#include <bits/stdc++.h>
using namespace std;

const int n = 6012074;
int d[n][2];

int main() {
    freopen("degree.txt", "r", stdin);
    for (int i = 0; i < n; i++) scanf("%d,%d", &d[i][0], &d[i][1]);
    int x = 0, y = 0;
    for (int i = 0; i < n; i++) x += d[i][0], y += d[i][1];
    int z[2] = {0, 0};
    for (int i = 0; i < n; i++) {
        if (!d[i][0]) z[0]++;
        if (!d[i][1]) z[1]++;
    }
    printf("%lf\n%lf\n", (double)x / n, (double)y / n);
    printf("%d %d\n", z[0], z[1]);


    freopen("reciprocity.txt", "r", stdin);
    double ans = 0;
    for (int i = 0; i < n; i++) {
        double x; scanf("%lf", &x);
        ans += x;
    }
    printf("%lf\n", ans / n);
}
