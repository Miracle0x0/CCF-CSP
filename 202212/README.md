# 2022 年 12 月 CSP

## 202212-1 现值计算

### 题解

看懂题目即可，注意用 double 类型。

### 代码

- [p1.cpp](./p1.cpp)

```cpp
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
```

## 202212-2 训练计划

### 题解

最早开始时间容易确定，记录每个科目前面依赖的科目的开始时间即可，由于依赖的科目总是小于当前科目因此一次遍历即可完成。

最晚开始时间由于每个科目可能被它后面的若干个科目依赖，需要再进行一次遍历，找到依赖它的科目的最晚开始时间最小的科目，然后根据当前科目所需的时间确定。

### 代码

- [p2.cpp](./p2.cpp)

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXM = 100 + 5, MAXN = 365 + 1;

int n, m;
int d[MAXM], t[MAXM];
int earliest[MAXM], latest[MAXM];

int main() {
    // freopen("./in.txt", "r", stdin);
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; i++) scanf("%d", &d[i]);
    for (int i = 1; i <= m; i++) scanf("%d", &t[i]);
    bool onTime = true;
    for (int i = 1; i <= m; i++) {
        earliest[i] = d[i] ? earliest[d[i]] + t[d[i]] : 1;
        if (earliest[i] + t[i] - 1 > n)
            onTime = false;
    }
    for (int i = 1; i <= m; i++)
        printf(" %d" + !(i - 1), earliest[i]);
    putchar('\n');
    if (onTime) {
        for (int i = m; i >= 1; i--) {
            int tmp = MAXN;
            for (int j = i + 1; j <= m; j++) {
                if (d[j] == i) tmp = min(tmp, latest[j]);
            }
            latest[i] = (tmp == MAXN) ? n - t[i] + 1 : tmp - t[i];
        }
        for (int i = 1; i <= m; i++)
            printf(" %d" + !(i - 1), latest[i]);
    }
    return 0;
}
```

## 202212-3 JPEG 解码

### 题解

这一次的第三题相对以往难度下降了不少，唯一可能的“坎”就是 Z 字形填数，思路整理清楚了就能轻松拿下。

### 代码

- [p3.cpp](./p3.cpp)

```cpp
#include <bits/stdc++.h>
using namespace std;

const double PI = acos(-1);

int n, T;
int Q[8][8], M[8][8], M1[8][8], P[65];

double alphaFunc(int x) {
    if (x == 0) return sqrt(0.5);
    return 1.0;
}

void showMat(int mat[8][8]) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++)
            printf(" %d" + !j, mat[i][j]);
        putchar('\n');
    }
}

int main() {
    // freopen("./in.txt", "r", stdin);
    // input Q
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++)
            scanf("%d", &Q[i][j]);
    }
    scanf("%d", &n);
    scanf("%d", &T);
    for (int i = 0; i < n; i++) scanf("%d", &P[i]);
    // input M
    int k = 0;
    int a = 0, b = 0;
    M[a][b] = P[k++];
    while (k < n) {
        if (b == 7)
            M[++a][b] = P[k++];
        else
            M[a][++b] = P[k++];
        if (k >= n)
            break;
        while (k < n && a < 7 && b > 0)
            M[++a][--b] = P[k++];
        if (k >= n)
            break;
        if (a == 7)
            M[a][++b] = P[k++];
        else
            M[++a][b] = P[k++];
        if (k >= n)
            break;
        while (k < n && a > 0 && b < 7)
            M[--a][++b] = P[k++];
    }
    // switch T
    if (T == 0) {
        showMat(M);
        return 0;
    }
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++)
            M[i][j] *= Q[i][j];
    }
    if (T == 1) {
        showMat(M);
        return 0;
    }
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            double sum = 0;
            for (int u = 0; u < 8; u++) {
                for (int v = 0; v < 8; v++)
                    sum += alphaFunc(u) * alphaFunc(v) * M[u][v] * cos(PI / 8 * (i + 0.5) * u) * cos(PI / 8 * (j + 0.5) * v);
            }
            M1[i][j] = int(sum / 4 + 128 + 0.5);
            if (M1[i][j] > 255)
                M1[i][j] = 255;
            else if (M1[i][j] < 0)
                M1[i][j] = 0;
        }
    }
    showMat(M1);
    return 0;
}
```
