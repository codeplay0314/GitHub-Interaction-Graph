#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize(3, "Ofast", "inline")

const int maxn = 6012074;
const int maxm = 42700112;
int n = 6012074;

namespace G {
    int head[maxn], to[maxm<<1], nxt[maxm<<1], cnt;
    void insert(int x, int y) {
            to[cnt] = y, nxt[cnt] = head[x], head[x] = cnt++;
            to[cnt] = x, nxt[cnt] = head[y], head[y] = cnt++;
    }
    void init() {
        memset(head, -1, n<<2);
    }
}

int d[maxn];
struct stack {
    int a[maxn], p;
    inline int top() { return a[p - 1]; } 
    inline void push(int x) { a[p++] = x; }
    inline void pop() { p--; }
    inline bool empty() { return !p; }
    inline void init() { p = 0; }
}S;
struct queue {
    int a[maxn], p1, p2;
    inline void push(int x) { a[p2++] = x; }
    inline int front() { return a[p1]; }
    inline void pop() { p1++; }
    inline bool empty() { return p1 == p2; }
    inline void init() { p1 = p2 = 0; }
}Q;
vector<int> P[maxn];
double BC[maxn];
double theta[maxn], sigma[maxn];
int num = 0;
void bfs(int s) {
    S.init();
    Q.init();
    memset(d, -1, n<<2);
    memset(sigma, 0, n<<3);
    memset(theta, 0, n<<3);
    sigma[s] = 1, d[s] = 0, Q.push(s);
    int sum1 = 0, sum2 = 0, sum3 = 0, sum4 = 0;
    while (!Q.empty()) {
        sum1++;
        int v = Q.front(); Q.pop();
        S.push(v);
        for (int i = G::head[v]; i >= 0; i = G::nxt[i]) {
            sum2++;
            int w = G::to[i];
            if (d[w] < 0) Q.push(w), d[w] = d[v] + 1;
            if (d[w] == d[v] + 1) sigma[w] += sigma[v], P[w].push_back(v);
        }
    }
    while (!S.empty()) {
        sum3++;
        int w = S.top(); S.pop();
        for (int i = 0, lim = P[w].size(); i < lim; i++) {
            sum4++;
            int v = P[w][i];
            theta[v] += 1.0 * sigma[v] / sigma[w] * (1 + theta[w]);
        }
        P[w].clear();
        if(w != s) BC[w] += theta[w]; 
    }
    fprintf(stderr, "%d finished: %d %d %d %d\n", num++, sum1, sum2, sum3, sum4);
}

int main(int argc, char *argv[]) {
    // freopen("graph.txt", "r", stdin);
    freopen("G.edgelist", "r", stdin);
    
    G::init();
    int x, y;
    while (~scanf("%d%d", &x, &y)) G::insert(x, y);
//  This place we can seperate the real_n into several parts to run parallel computing.
    int t, p;
    sscanf(argv[1], "%d", &t);
    sscanf(argv[2], "%d", &p);
    for (int i = p - 1; i < n; i += t) bfs(i);

    string str = "bc";
    str += p + '0';
    str += ".txt";
    char outfile[20];
    for (int i = 0; i < str.length(); i++) outfile[i] = str[i];
    outfile[str.length()] = 0;
    freopen(outfile, "w", stdout);
    for (int i = 0; i < n; i++) printf("%.9lf\n", BC[i]);
    return 0;
}
