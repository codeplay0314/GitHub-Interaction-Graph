#include <bits/stdc++.h>
using namespace std;

const int maxn = 6012074;
const int maxm = 42700112;
struct Node{
    int in, out, tot, no;
}a[maxn];

bool cmp1(const Node A, const Node B) {
    return A.in < B.in;
}
bool cmp2(const Node A, const Node B) {
    return A.out < B.out;
}
bool cmp3(const Node A, const Node B) {
    return A.tot < B.tot;
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
        a[x].out++, a[y].in++;
    }

    for (int i = 0; i < n; i++) {
        a[i].tot = a[i].in + a[i].out;
        a[i].no = i;
    }

    int bap = 0;
    for (int i = 0; i < n; i++)
        if (a[i].in <= 2 * a[i].out && a[i].out <= 2 * a[i].in) bap++;

    FILE *fp = fopen("result.txt", "w");
    fprintf(fp, "%lf%% nodes are balanced\n\n", 100.0 * bap / n);

    
    sort(a, a + n, cmp1);
    fprintf(fp, "Top 10 largest incoming degree:\n");
    for (int i = 0; i < 10; i++) fprintf(fp, "%d: %d\n", a[n - i - 1].no, a[n - i - 1].in);
    fprintf(fp, "\n");
    fprintf(fp, "Top 10 smallest incoming degree:");
    for (int i = 0; i < 10; i++) fprintf(fp, " %d", a[i].in);
    fprintf(fp, "\n");

    sort(a, a + n, cmp2);
    fprintf(fp, "Top 10 largest outcoming degree:\n");
    for (int i = 0; i < 10; i++) fprintf(fp, "%d: %d\n", a[n - i - 1].no, a[n - i - 1].out);
    fprintf(fp, "\n");
    fprintf(fp, "Top 10 smallest outcoming degree:");
    for (int i = 0; i < 10; i++) fprintf(fp, " %d", a[i].out);
    fprintf(fp, "\n");
    
    sort(a, a + n, cmp3);
    fprintf(fp, "Top 10 largest total degree:\n");
    for (int i = 0; i < 10; i++) fprintf(fp, "%d: %d\n", a[n - i - 1].no, a[n - i - 1].tot);
    fprintf(fp, "\n");
    fprintf(fp, "Top 10 smallest total degree:");
    for (int i = 0; i < 10; i++) fprintf(fp, " %d", a[i].tot);
    fprintf(fp, "\n");

    for (int i = 0; i < n; i++)
        fprintf(outfile, "%d,%d\n", a[i].in, a[i].out);

    return 0;
}
