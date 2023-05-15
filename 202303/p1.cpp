#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e4 + 5;

int n, a, b;
int xx1, xx2, yy1, yy2;
int res;

int main() {
    // freopen("./in.txt", "r", stdin);
    scanf("%d %d %d", &n, &a, &b);
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d %d", &xx1, &yy1, &xx2, &yy2);
        if (xx1 < 0) xx1 = 0;
        if (xx1 > a) xx1 = a;
        if (xx2 < 0) xx2 = 0;
        if (xx2 > a) xx2 = a;
        if (yy1 < 0) yy1 = 0;
        if (yy1 > b) yy1 = b;
        if (yy2 < 0) yy2 = 0;
        if (yy2 > b) yy2 = b;
        res += (xx2 - xx1) * (yy2 - yy1);
    }
    printf("%d\n", res);
    return 0;
}