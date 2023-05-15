#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 5;

int n, m, k;
int t[MAXN], c[MAXN];
int L, R, res;

bool judge(int cur) {
    int resource = 0;
    for (int i = 0; i < n; i++) {
        if (t[i] > cur) {
            resource += (t[i] - cur) * c[i];
            if (resource > m) return false;
        }
    }
    return resource <= m;
}

int main() {
    // freopen("./in.txt", "r", stdin);
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &t[i], &c[i]);
        R = max(R, t[i]);
    }
    L = k;
    while (L <= R) {
        int mid = (L + R) / 2;
        // printf("mid: %d\n", mid);
        if (judge(mid)) {
            res = mid;
            R = mid - 1;
        } else {
            L = mid + 1;
        }
    }
    printf("%d\n", res);
    return 0;
}