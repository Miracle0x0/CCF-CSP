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

## 202203-3 计算资源调度器

### 题解

本来想用 vector 直接存节点，但发现初始化有问题？算了还是用 map 吧。

### 代码

- [p3.cpp](./p3.cpp)

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, m, g;                // 节点数量，可用区数量，计算任务组数
int f, a, na, pa, paa, paar;// 任务数，应用编号，节点所属的可用区编号，与应用运行在同一个可用区，不和应用的任务运行在同一个可用区，必须满足

// 节点
struct Node {
    int idx;       // 编号
    int area;      // 所属的可用区
    int nums = 0;  // 当前在其上运行的任务数量
    set<int> tasks;// 当前在其上运行的应用编号

    Node() = default;
    Node(int idx, int area) : idx(idx), area(area) {}

    bool operator<(const Node &nn) const {
        if (nums == nn.nums) return idx < nn.idx;// 任务数量相同时编号小的优先
        return nums < nn.nums;                   // 任务数量少的优先
    }
};

// 节点信息列表
unordered_map<int, Node> nodes;

// 节点排序函数
bool compareNode(const int &a, const int &b) {
    return nodes[a] < nodes[b];
}

// 获得可用区 x 内的计算节点编号
void getNodes(int x, vector<int> &tmp) {
    for (auto it = tmp.begin(); it != tmp.end();) {
        if (nodes[*it].area != x) tmp.erase(it);
        else
            it++;
    }
}

// 与应用 x 的任务在同一个可用区
void getSameAreaWith(int x, vector<int> &tmp) {
    set<int> areas;
    for (auto it = nodes.begin(); it != nodes.end(); it++) {
        if (it->second.tasks.count(x))// 包含应用 x 的任务
            areas.insert(it->second.area);
    }
    for (auto it = tmp.begin(); it != tmp.end();) {
        if (!areas.count(nodes[*it].area))// 排除不在 areas 中的可用区编号
            tmp.erase(it);
        else
            it++;
    }
}

// 不能与应用 x 的任务在同一个节点
auto getDiffNode(int x, vector<int> tmp) {
    for (auto it = tmp.begin(); it != tmp.end();) {
        if (nodes[*it].tasks.count(x))
            tmp.erase(it);
        else
            it++;
    }
    return tmp;
}

int main() {
    // freopen("./in.txt", "r", stdin);
    scanf("%d %d", &n, &m);
    vector<int> considerable;
    for (int i = 1, l; i <= n; i++) {
        scanf("%d", &l);// 编号为 i 的计算节点位于编号为 l 的可用区
        nodes.insert(make_pair(i, Node(i, l)));
        considerable.push_back(i);
    }
    scanf("%d", &g);
    for (int i = 1; i <= g; i++) {
        scanf("%d %d %d %d %d %d", &f, &a, &na, &pa, &paa, &paar);
        // f 个应用 a 的任务
        while (f--) {
            vector<int> tmp1 = considerable, tmp2;
            if (na) {              // 节点亲和性要求
                getNodes(na, tmp1);// 获得可用区 na 内的节点编号
            }
            if (pa) {                     // 任务亲和性要求
                getSameAreaWith(pa, tmp1);// 获得与应用 pa 的任务在同一个可用区的节点编号
            }
            if (paa) {                        // 任务反亲和性要求
                tmp2 = getDiffNode(paa, tmp1);// 与应用 x 的任务不在同一个节点编号
            }
            // 尝试寻找可用的节点
            if (tmp1.empty() || paar && tmp2.empty()) {// 无可用节点或没有满足非亲和的节点
                printf("0 ");
                continue;
            }
            if (!paar && tmp2.empty())// 没有满足非亲和性的节点，但为尽量满足
                tmp2 = tmp1;
            sort(tmp2.begin(), tmp2.end(), compareNode);
            // 更新节点信息
            int idx = tmp2[0];
            nodes[idx].nums++;
            nodes[idx].tasks.insert(a);
            printf("%d ", nodes[idx].idx);
        }
        putchar('\n');
    }
    return 0;
}
```
