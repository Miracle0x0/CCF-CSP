#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 5;

int n, k, x, y, sum;
int a[MAXN];

int main() {
    // freopen("./in.txt", "r", stdin);
    a[0] = 1;
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= k; i++) {
        scanf("%d %d", &x, &y);
        if (!a[y]) sum++;
        a[x] = 1;
    }
    printf("%d\n", sum);
    return 0;
}