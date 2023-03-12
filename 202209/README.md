# 2022 年 9 月 CSP

## 202209-1 如此编码

### 题解

题目最下方给出了提示。

### 代码

- [p1.cpp](./p1.cpp)

```cpp
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
```

## 202209-2 何以包邮？

### 题解

这道题我在考场上使用的解法是搜索+剪枝，也可以使用动态规划进行求解。

- 搜索+剪枝

### 代码

- [p2-dfs.cpp](./p2-dfs.cpp)

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, x;
int a[35], sum[35];
int min_cost;

void dfs(int idx, int cost) {
	if (min_cost == x) return;
	// if (cost > min_cost) return;
	if (cost == x) {
		min_cost = x;
		return;
	}
	if (cost > x) min_cost = min(min_cost, cost);
	if (idx > n) return;
	if (cost + sum[n] - sum[idx - 1] < x) return;
	dfs(idx + 1, cost); //不选
	if (cost + a[idx] > min_cost) return;
	dfs(idx + 1, cost + a[idx]); //选
}

int main() {
	// freopen("in.txt", "r", stdin);
	scanf("%d %d", &n, &x);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]), min_cost += a[i];
	// sort(a + 1, a + 1 + n);
	for (int i = 1; i <= n; i++) sum[i] = sum[i - 1] + a[i];
	dfs(1, 0);
	printf("%d\n", min_cost);
	return 0;
}
```

- 动态规划

### 代码

- [p2.cpp](./p2.cpp)

```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 30 + 5, MAXA = 1e4 + 5;

int n, x, sum;
int a[MAXN], dp[MAXN * MAXA];

int main() {
    // freopen("./in.txt", "r", stdin);
    scanf("%d %d", &n, &x);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]), sum += a[i];
    for (int i = 1; i <= n; i++) {
        for (int j = sum; j >= a[i]; j--) {
            dp[j] = max(dp[j], dp[j - a[i]] + a[i]);
        }
    }
    for (int i = x; i <= sum; i++) {
        if (dp[i] >= x) {
            printf("%d\n", i);
            break;
        }
    }
    return 0;
}
```
