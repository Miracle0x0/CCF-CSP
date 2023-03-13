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

## 202209-3 防疫大数据

### 题解

数据量足以支持暴力模拟。对于每个地区用 map 存储对应的风险区间。当风险日期发生变化时，检查与原来记录的区间是否相交。

对于每一天的风险人员列表，直接查找 7 天内到过该地的所有人员，判断到达日期是否位于风险区间。

考虑到可能存在的重复数据，用 set 可以消除多余的输出。

### 代码

- [p3.cpp](./p3.cpp)

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MAXN = 1000 + 5;

int n;
// 地区 x 被认定为风险地区的日期区间为 [a, b]，记作 G[x] = {a, b}
map<LL, pair<int, int>> G;
// 当日收到的风险地区信息的数量、当日收到的漫游数据的条目数量、当日收到的风险地区的列表
int r[MAXN], m[MAXN], p[MAXN][MAXN];
// 一条漫游数据中的日期、用户和地区
int d[MAXN][MAXN], u[MAXN][MAXN], reg[MAXN][MAXN];
// 风险用户列表
set<int> s;

void showRiskList(int date) {
    printf("%d", date);
    for (auto it = s.begin(); it != s.end(); it++)
        printf(" %d", *it);
    putchar('\n');
}

int main() {
    freopen("./in.txt", "r", stdin);
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &r[i], &m[i]);
        s.clear();
        for (int j = 1; j <= r[i]; j++) {
            scanf("%d", &p[i][j]);
            int pre_date = G[p[i][j]].first;
            int end_date = G[p[i][j]].second;
            if (pre_date == end_date)// 非疫情区域
                G[p[i][j]] = make_pair(i, i + 6);
            else if (end_date >= i - 1)
                G[p[i][j]] = make_pair(pre_date, i + 6);
            else
                G[p[i][j]] = make_pair(i, i + 6);
        }
        for (int j = 1; j <= m[i]; j++)
            scanf("%d %d %d", &d[i][j], &u[i][j], &reg[i][j]);
        for (int day = max(i - 6, 0); day <= i; day++) {// 从当前日期的一星期前开始统计
            for (int j = 1; j <= m[day]; j++) {
                int date = d[day][j];
                if (date < i - 6) continue;
                int pre_date = G[reg[day][j]].first;
                int end_date = G[reg[day][j]].second;
                // 当前日期在风险区间内且用户到达该地的日期在风险区间内
                if (i >= pre_date && i <= end_date && date >= pre_date && date <= end_date && end_date != pre_date)
                    s.insert(u[day][j]);
            }
        }
        showRiskList(i);
    }
    return 0;
}
```
