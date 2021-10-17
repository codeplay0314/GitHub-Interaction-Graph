#include <bits/stdc++.h>
using namespace std;

const int maxn = 6012074;
const int maxm = 42700112;
int com[maxn];

struct Edge {
    int to[maxm], nxt[maxm], head[maxn], cnt;
    void insert(int u, int v) {
        to[cnt] = v, nxt[cnt] = head[u], head[u] = cnt++;
    }
    Edge() {
        cnt = 0;
        memset(head, -1, sizeof(head));
    }
}e, ne;

int main() {
    int n = maxn, m = maxm;
    FILE *input = fopen("/bdata/yingqiu/year_span/PR_IC_W_interaction.edgelist", "r");
    for (int i = 0, u, v; i < m; i++) {
        fscanf(input, "%d%d", &u, &v);
        e.insert(u, v);
        ne.insert(v, u);
    }
    fclose(input);
    input = fopen("/bdata/yingqiu/year_span/findSHS/louvain/1102_brand_new_community.txt", "r");
    for (int i = 0; i < n; i++)
        fscanf(input, "%d%d", &i, &com[i]);
    fclose(input);
    FILE *output = fopen("num_connected_community.txt", "w");    
    for (int u = 0; u < n; u++) {
        set<int> s[3];
        for (int i = e.head[u]; i >= 0; i = e.nxt[i]) {
            int v = e.to[i];
            s[0].insert(com[v]);
            s[2].insert(com[v]);
        }
        for (int i = ne.head[u]; i >= 0; i = ne.nxt[i]) {
            int v = ne.to[i];
            s[1].insert(com[v]);
            s[2].insert(com[v]);
        }
        fprintf(output, "%d %d %d\n", s[0].size(), s[1].size(), s[2].size());
    }
    return 0;
}