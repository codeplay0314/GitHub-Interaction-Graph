#include <bits/stdc++.h>
using namespace std;

const int maxn = 6012074;
int scc[maxn];
int sum[maxn];

int main() {
    FILE *fi = fopen("scc.txt", "r");
    FILE *fo = fopen("result.txt", "w");
    if (!fi) exit(0);

    int n = 1510452;
    int maxs = 0, LSCC;
    for (int i = 0; i < n; i++) {
        fscanf(fi, "%d", &scc[i]);
        sum[scc[i]]++;
        if (maxs < sum[scc[i]]) maxs = sum[scc[i]], LSCC = scc[i];
    }

    fprintf(fo, "LSCC: %d\n", LSCC);

    return 0;
}
