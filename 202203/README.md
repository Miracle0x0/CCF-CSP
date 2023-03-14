# 2022 年 3 月 CSP

## 202203-1 未初始化警告

### 题解

用一个数组标记是否初始化过，只要在左侧出现过就将其置为 1，否则 0 代表未初始化。

### 代码

- [p1.cpp](./p1.cpp)

```cpp
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
```

## 202203-2 出行计划

### 题解

要想进入某个场所，那么做核酸的时间点必须在区间 [$t_i - c_i - k + 1, t_i - k$] 内。

用差分数组记录，最后还原得到原始数组。

### 代码

- [p2.cpp](./p2.cpp)

```cpp
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
```
