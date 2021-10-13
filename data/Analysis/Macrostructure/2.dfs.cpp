#include <bits/stdc++.h>
using namespace std;

inline char getc() {
  static const int maxl = 1e6;
  static char buf[maxl], *p1 = buf, *p2 = buf;
  return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, maxl, stdin), p1 == p2)? EOF: *p1++;
}
inline bool isdigit(char c) {
  return '0' <= c && c <= '9';
}
inline int read() {
  int x = 0; char c = getchar();
  while (!isdigit(c)) c = getchar();
  while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
  return x;
}

const int maxn = 6012074;
const int maxm = 42700112;
int type[maxn], rk[maxn];

struct Edge {
  int to[maxm], w[maxm], nxt[maxm], cur[maxn], cnt;
  void insert(int u, int v, int c) {
    to[cnt] = v, w[cnt] = c, nxt[cnt] = cur[u], cur[u] = cnt++;
  }
  Edge() {
    memset(cur, -1, sizeof(cur));
  }
}e, re;

bool con[maxn];
bool vis[maxn];
void dfs1(int u, int d) {
  if (d) type[u] = 2, rk[u] = d, vis[u] = true;
  for (int i = e.cur[u]; i >= 0; i = e.nxt[i]) {
    int v = e.to[i];
    if (!vis[v]) dfs1(v, d + 1);
  }
}
void dfs2(int u, int d) {
  if (d) type[u] = 3, rk[u] = d, vis[u] = true;
  for (int i = re.cur[u]; i >= 0; i = re.nxt[i]) {
    int v = re.to[i];
    if (!vis[v]) dfs2(v, d + 1);
  }
}
void dfs3(int u, int d) {
  if (d) type[u] = 5, rk[u] = d, vis[u] = true;
  for (int i = e.cur[u]; i >= 0; i = e.nxt[i]) {
    int v = e.to[i];
    if (!vis[v]) dfs3(v, d + 1);
  }
}
void dfs4(int u, int d) {
  if (!type[u]) type[u] = 6, rk[u] = d;
  else if (type[u] == 5) type[u] = 4;
  vis[u] = true;
  for (int i = re.cur[u]; i >= 0; i = re.nxt[i]) {
    int v = re.to[i];
    if (!vis[v]) dfs4(v, d + 1);
  }
}


int main() {
  freopen("NewGraph.txt", "r", stdin);
  freopen("scctype.txt", "w", stdout);
  memset(rk, -1, sizeof(rk));
  int n = read(), m = read();
  int root = 409858;
  for (int i = 0, u, v, w; i < m; i++) {
    u = read(), v = read(), w = read();
    e.insert(u, v, w);
    re.insert(v, u, w);
    con[u] = con[v] = true;
  }

  type[root] = 1, vis[root] = true;
  dfs1(root, 0);
  dfs2(root, 0);
  for (int i = 0; i < n; i++)
    if (type[i] == 3) dfs3(i, 0);
  memset(vis, 0, sizeof(vis));
  for (int i = 0; i < n; i++)
    if (type[i] == 2) dfs4(i, 0);
  for (int i = 0; i < n; i++)
    if (!type[i] && con[i]) type[i] = 7;

  for (int i = 0; i < n; i++) printf("%d %d\n", type[i], rk[i]);
  return 0;
}
