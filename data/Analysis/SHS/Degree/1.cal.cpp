#include <bits/stdc++.h>
using namespace std;

const int maxn = 6012074;
const int maxm = 42700112;
int in[maxn], out[maxn];

int main() {
    int n = maxn, m = maxm;
    FILE *input = fopen("/bdata/yingqiu/year_span/PR_IC_W_interaction.edgelist", "r");
    for (int i = 0, u, v; i < m; i++) {
        fscanf(input, "%d%d", &u, &v);
        out[u]++, in[v]++;
    }
    fclose(input);
    FILE *output = fopen("degree.txt", "w");
    for (int i = 0; i < n; i++)
        fprintf(output, "%d %d %d\n", in[i], out[i], in[i] + out[i]);
    printf("%d\n", in[2444840]);
    printf("%d\n", in[3676700]);
    return 0;
}