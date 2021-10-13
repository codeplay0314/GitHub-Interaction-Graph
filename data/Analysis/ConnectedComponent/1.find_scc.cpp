#include <bits/stdc++.h>
using namespace std;

const int maxn = 6012074;
const int maxm = 42700112;
int scc[maxn], sum;
int num[maxn];

struct Edge {
    int to[maxm], nxt[maxm], cur[maxn], cnt;
    void insert(int x, int y) {
        to[cnt] = y, nxt[cnt] = cur[x], cur[x] = cnt++;
    }
    Edge() {
        memset(cur, -1, sizeof(cur));
    }
}e;

stack<int> st;
bool ins[maxn];
int dfn[maxn], low[maxn];
void Tarjan (int u) {
  static int count = 0;
  dfn[u] = low[u] = ++count;
  st.push(u), ins[u] = true;
  for (int i = e.cur[u]; i >= 0; i = e.nxt[i]) {
    int v = e.to[i];
    if (!dfn[v]) {
      Tarjan(v);
      low[u] = min(low[u], low[v]);
    }
    else if (ins[v]) low[u] = min(low[u], dfn[v]);
  }
  if (dfn[u] == low[u]) {
    int now;
    do {
      now = st.top(); st.pop();
      scc[now] = sum;
      ins[now] = false;
      num[sum]++;
    }while(now != u);
    sum++;
  }
}

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
        e.insert(x, y);
    }

    for (int i = 0; i < n; i++)
        if (!dfn[i]) Tarjan(i);

    for (int i = 0; i < n; i++)
        fprintf(outfile, "%d\n", scc[i]);
    sort(num, num + sum);
    printf("There are %d components.\nTop components:", sum);
    for (int i = 0; i < 10; i++) {
        if (sum - i - 1 < 0) break;
        printf(" %d", num[sum - i - 1]);
    }
    putchar('\n');

    return 0;
}
