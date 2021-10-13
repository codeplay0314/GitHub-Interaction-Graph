#include <bits/stdc++.h>
using namespace std;

const int maxn = 6012074;
const int maxm = 42700112;
int scc[maxn];
struct Edge {
  int u, v;
  bool operator < (const Edge e) const {
    return u < e.u || (u == e.u && v < e.v);
  }
  bool operator == (const Edge e) const {
    return u == e.u && v == e.v;
  }
}e[maxm];

struct NGraph {
  int u, v, w;
}ne[maxm];

int main(int argc, char *argv[]) {
    if (argc != 6) {
        printf("Please enter parameters: n, m, num of scc, input file, output file\n");
        exit(0);
    }
    FILE *file1 = fopen("scc.txt", "r");
    FILE *file2 = fopen(argv[4], "r");
    FILE *file3 = fopen(argv[5], "w");
    if (file1 == NULL || file2 == NULL) exit(0);

    int n, m, nn, nm = 0;
    sscanf(argv[1], "%d", &n);
    sscanf(argv[2], "%d", &m);
    sscanf(argv[3], "%d", &nn);
    for (int i = 0; i < n; i++) fscanf(file1, "%d", &scc[i]);
    for (int i = 0, u, v; i < m; i++) {
        fscanf(file2, "%d%d", &u, &v);
        e[i] = (Edge){scc[u], scc[v]};
    }
    sort(e, e + m);
    for (int i = 0; i < m; i++)
        if (e[i].u != e[i].v)
            if (i && e[i] == e[i - 1]) ne[nm - 1].w++;
            else ne[nm++] = (NGraph){e[i].u, e[i].v, 1};
    fprintf(file3, "%d %d", nn, nm);
    for (int i = 0; i < nm; i++) fprintf(file3, "\n%d %d %d", ne[i].u, ne[i].v, ne[i].w);
    return 0;
}
