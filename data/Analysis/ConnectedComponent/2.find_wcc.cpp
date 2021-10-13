#include <bits/stdc++.h>
using namespace std;

const int maxn = 6012074;
const int maxm = 42700112;
int num[maxn];

struct Union {
    int fa[maxn];
    inline int find(int x) {
        return x == fa[x]? x: fa[x] = find(fa[x]);
    }
    inline void unite(int x, int y) {
        fa[find(y)] = find(x);
    }
    void init(int n) {
        for (int i = 0; i < n; i++) fa[i] = i;
    }
}uni;

int main(int argc, char *argv[]) {
    int n, m;
    if (argc != 5) {
        printf("Please enter parameters: n, m, input file, output file\n");
        exit(0);
    }
    sscanf(argv[1], "%d", &n);
    sscanf(argv[2], "%d", &m);
    FILE *infile = fopen(argv[3], "r");
    FILE *outfile = fopen(argv[4], "w");
    if (infile == NULL || outfile == NULL) exit(0);

    uni.init(n);
    for (int i = 0; i < m; i++) {
        int x, y;
        fscanf(infile, "%d%d", &x, &y);
        uni.unite(x, y);
    }

    for (int i = 0; i < n; i++) {
        fprintf(outfile, "%d\n", uni.find(i));
        num[uni.find(i)]++;
    }
    sort(num, num + n);

    int t = 0;
    while (!num[t]) t++;
    printf("There are %d components.\nTop components:", n - t);
    for (int i = 0; i < 10; i++) {
        if (n - i - 1 < 0) break;
        if (!num[n - i - 1]) break;
        printf(" %d", num[n - i - 1]);
    }
    putchar('\n');

    return 0;
}
