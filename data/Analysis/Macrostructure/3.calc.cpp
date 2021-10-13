#include <bits/stdc++.h>
using namespace std;

const int maxn = 6012074;
const int maxm = 42700112;
int scc[maxn], block[maxn];
int type[maxn];
int node[8], edge[12];
char name[8][20] = {"DISCONNECTED", "LSCC", "OUT", "IN", "BRIDGES", "IN-TENDRILS", "OUT-TENDRILS", "OTHER"};
int to[12][2] = {{1, 2}, {3, 1}, {3, 5}, {7, 5}, {6, 7}, {3, 4}, {3, 2}, {4, 5}, {6, 5}, {4, 2}, {6, 2}, {6, 4}};

int main(int argc, char *argv[]) {
    int n, m, sccn;
    if (argc != 6) {
        printf("Please enter parameters: n, m, num of scc, input file, output file\n");
        exit(0);
    }
    FILE *file1 = fopen("../ConnectedComponent/scc.txt", "r");
    FILE *file2 = fopen("scctype.txt", "r");
    FILE *file3 = fopen(argv[4], "r");
    FILE *file4 = fopen(argv[5], "w");
    if (file1 == NULL || file2 == NULL) exit(0);

    sscanf(argv[1], "%d", &n);
    sscanf(argv[2], "%d", &m);
    sscanf(argv[3], "%d", &sccn);
    for (int i = 0; i < n; i++) fscanf(file1, "%d", &scc[i]);
    for (int i = 0, x; i < sccn; i++) fscanf(file2, "%d%d", &type[i], &x);
    for (int i = 0; i < n; i++) block[i] = type[scc[i]], node[block[i]]++;
    for (int i = 0, u, v; i < m; i++) {
        fscanf(file3, "%d%d", &u, &v);
        u = block[u], v = block[v];
        for (int j = 0; j < 12; j++)
            if (u == to[j][0] && v == to[j][1]) {
                edge[j]++;
                break;
            }
    }
    fprintf(file4, "NODES:\n");
    for (int i = 0; i < 8; i++) fprintf(file4, "%s: %d\n", name[i], node[i]);
    fprintf(file4, "\nEDGES:\n");
    for (int i = 0; i < 12; i++) fprintf(file4, "%s -> %s: %d\n", name[to[i][0]], name[to[i][1]], edge[i]);
    return 0;
}
