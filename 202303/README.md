# 2023 年 3 月 CSP

## 202303-1 田地丈量

### 题解

检测边界，超出边界的值用边界值代替。

### 代码

- [p1.cpp](./p1.cpp)

```cpp
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
```

## 202303-2 垦田计划

### 题解

二分答案，初始下界为 k，初始上界为 $max\{t_1, t_2, \cdots, t_n\}$。

### 代码

- [p2.cpp](./p2.cpp)

```cpp
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
```
