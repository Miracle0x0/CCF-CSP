#include <bits/stdc++.h>
using namespace std;
const int MAXM = 100 + 5, MAXN = 365 + 1;

int n, m;
int d[MAXM], t[MAXM];
int earliest[MAXM], latest[MAXM];

int main() {
    // freopen("./in.txt", "r", stdin);
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; i++) scanf("%d", &d[i]);
    for (int i = 1; i <= m; i++) scanf("%d", &t[i]);
    bool onTime = true;
    for (int i = 1; i <= m; i++) {
        earliest[i] = d[i] ? earliest[d[i]] + t[d[i]] : 1;
        if (earliest[i] + t[i] - 1 > n)
            onTime = false;
    }
    for (int i = 1; i <= m; i++)
        printf(" %d" + !(i - 1), earliest[i]);
    putchar('\n');
    if (onTime) {
        for (int i = m; i >= 1; i--) {
            int tmp = MAXN;
            for (int j = i + 1; j <= m; j++) {
                if (d[j] == i) tmp = min(tmp, latest[j]);
            }
            latest[i] = (tmp == MAXN) ? n - t[i] + 1 : tmp - t[i];
        }
        for (int i = 1; i <= m; i++)
            printf(" %d" + !(i - 1), latest[i]);
    }
    return 0;
}