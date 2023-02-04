#include <bits/stdc++.h>
using namespace std;

const int MAXN = 20 + 5;

int n, m;
int last_b = 0;
int a[MAXN], c[MAXN] = {1};

int main() {
    // freopen("./in.txt", "r", stdin);
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        c[i] = c[i - 1] * a[i];
    }
    for (int i = 1; i <= n; i++) {
        int b = m % c[i];
        printf("%d ", (b - last_b) / c[i - 1]);
        last_b = b;
    }
    return 0;
}