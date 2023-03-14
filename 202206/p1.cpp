#include <bits/stdc++.h>
#define SQR(x) ((x) * (x))
using namespace std;

const int MAXN = 1000 + 5;

int n;
double a[MAXN], sum;

int main() {
    // freopen("./in.txt", "r", stdin);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%lf", &a[i]), sum += a[i];
    double average_a = sum / n;
    double d_a = 0.0;
    for (int i = 1; i <= n; i++) {
        d_a += SQR(a[i] - average_a);
    }
    d_a /= n;
    for (int i = 1; i <= n; i++) {
        printf("%f\n", (a[i] - average_a) / sqrt(d_a));
    }
    return 0;
}