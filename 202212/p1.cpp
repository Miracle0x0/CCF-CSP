#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000 + 5;

int n;
double k, res, t;

int main() {
    // freopen("./in.txt", "r", stdin);
    scanf("%d %lf", &n, &k);
    for (int i = 0; i <= n; i++) {
        scanf("%lf", &t);
        res += t * pow(1 + k, -i);
    }
    printf("%f\n", res);
    return 0;
}