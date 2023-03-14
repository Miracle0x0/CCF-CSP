# 2022 年 6 月 CSP

## 202206-1 归一化处理

### 题解

简单题。

### 代码

- [p1.cpp](./p1.cpp)

```cpp
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
```

## 202206-2 寻宝！大冒险！

### 题解

整个地图太大，二维数组存不下。考虑到地图为稀疏矩阵，用 pair 存储每个为 1 的坐标，然后暴力查找即可。藏宝图较小可以直接使用二维数组存储。

### 代码

- [p2.cpp](./p2.cpp)

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXS = 50 + 5;

int n, L, S, sum;
set<pair<int, int>> all;
int s[MAXS][MAXS];

int main() {
    // freopen("./in.txt", "r", stdin);
    scanf("%d %d %d", &n, &L, &S);
    for (int i = 1, x, y; i <= n; i++) {
        scanf("%d %d", &x, &y);
        all.insert(make_pair(x, y));
    }
    for (int i = 0; i <= S; i++) {
        for (int j = 0; j <= S; j++)
            scanf("%d", &s[S - i][j]);
    }
    for (auto tmp: all) {
        int x = tmp.first, y = tmp.second;
        if (x > L - S || y > L - S) continue;
        // printf("init point: (%d, %d)\n", x, y);
        bool ok = true, fst = false;
        int x_offset, y_offset;
        for (int i = 0; i <= S; i++) {
            for (int j = 0; j <= S; j++) {
                if (!fst) {
                    x_offset = x - i, y_offset = y - j;
                    fst = true;
                }
                int tx = i + x_offset, ty = j + y_offset;
                // printf("cur point: (%d, %d)\n", tx, ty);
                if (s[i][j] == 1 && all.find(make_pair(tx, ty)) == all.end() ||
                    s[i][j] == 0 && all.find(make_pair(tx, ty)) != all.end()) {
                    ok = false;
                    break;
                }
            }
            if (!ok) break;
        }
        if (ok) sum++;
    }
    printf("%d\n", sum);
    return 0;
}
```
