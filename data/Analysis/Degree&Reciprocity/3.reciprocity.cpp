#include <bits/stdc++.h>
using namespace std;

const int maxn = 6012074;
const int maxm = 42700112;
int d[maxn], re[maxn];

struct Edge {
    int x, y;
    bool t;
    bool operator == (const Edge e) const {
        return x == e.x && y == e.y;
    }
    bool operator < (const Edge e) const {
        return x < e.x || (x == e.x && y < e.y) || (e == *this && t < e.t);
    }
}e[maxm * 2];

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

    for (int i = 0; i < m; i++) {
        int x, y;
        fscanf(infile, "%d%d", &x, &y);
        d[x]++, d[y]++;
        e[i * 2] = (Edge){x, y, 0};
        e[i * 2 + 1] = (Edge){y, x, 1};
    }
    sort(e, e + m * 2);

    int tot = 0;
    int p = 0, q = 0;
    while (p < m * 2) {
        while (q < m * 2 && e[p] == e[q]) q++;
        if (e[p].t != e[q - 1].t)
            for (int i = p; i < q; i++)
                if (!e[i].t) re[e[i].x]++, re[e[i].y]++, tot++;
                else break;
        p = q;
    }

    printf("Reciprocity of the Graph: %lf\n", (double)tot / m);
    for (int i = 0; i < n; i++) fprintf(outfile, "%.6lf\n", (double)re[i] / d[i]);

    return 0;
}
