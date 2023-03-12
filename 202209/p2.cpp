#include <bits/stdc++.h>
using namespace std;

const int MAXN = 30 + 5, MAXA = 1e4 + 5;

int n, x, sum;
int a[MAXN], dp[MAXN * MAXA];

int main() {
    // freopen("./in.txt", "r", stdin);
    scanf("%d %d", &n, &x);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]), sum += a[i];
    for (int i = 1; i <= n; i++) {
        for (int j = sum; j >= a[i]; j--) {
            dp[j] = max(dp[j], dp[j - a[i]] + a[i]);
        }
    }
    for (int i = x; i <= sum; i++) {
        if (dp[i] >= x) {
            printf("%d\n", i);
            break;
        }
    }
    return 0;
}