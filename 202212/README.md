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
