#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2e5 + 5;

int n, m, k, q;
int d[MAXN];

int main() {
    // freopen("./in.txt", "r", stdin);
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 1, t, c; i <= n; i++) {
        scanf("%d %d", &t, &c);
        d[max(0, t - c - k + 1)]++;
        d[max(0, t - k) + 1]--;
    }
    for (int i = 1; i < MAXN; i++) d[i] += d[i - 1];
    for (int i = 1; i <= m; i++) {
        scanf("%d", &q);
        printf("%d\n", d[q]);
    }
    return 0;
}