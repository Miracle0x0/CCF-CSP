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

## 202206-3 角色授权

### 题解

题目涉及到了多个对象，考虑使用类来表示每种对象。

设计三个类 `RoleInfo`, `UserInfo` 和 `GroupInfo`，分别对应角色、用户和用户组的相关信息，然后用 map 数组存储这些信息，命名为 `roles`, `users` 和 `groups`。

`RoleInfo` 类中有三个 set，记录操作清单、资源种类清单和资源名称清单；`UserInfo` 类中有两个 set，记录所属的角色和所属的用户组，并定义了 authCheck 方法用于校验权限；`GroupInfo` 中有一个 set，记录所属的角色。authCheck 方法按照题目描述的校验顺序和要求编写即可。

最后注意到每次查询的用户可能重复，**查询完毕需要清空用户所属的用户组信息**。

### 代码

- [p3.cpp](./p3.cpp)

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, m, q;// 角色数量，角色关联数量，待检查的操作数量
int nv, no, nn, ns, ng;

string name, tmp, objType, objName;
string userName, opName, RcType, RcName;

// 角色信息
class RoleInfo {
public:
    set<string> roleOpList;    // 操作清单
    set<string> roleRcTypeList;// 资源种类清单
    set<string> roleRcNameList;// 资源名称清单
};

map<string, RoleInfo> roles;// 角色

// 用户组信息
class GroupInfo {
public:
    set<string> roleList;// 所属的角色
};

map<string, GroupInfo> groups;// 用户组

// 用户信息
class UserInfo {
public:
    set<string> roleList;     // 所属的角色
    set<string> groupBelongTo;// 所属的用户组

    bool authCheck(string opName, string RcType, string RcName) {
        // 首先检查用户
        for (auto roleName: roleList) {
            // 检查操作清单
            if (roles[roleName].roleOpList.count("*") || roles[roleName].roleOpList.count(opName)) {
                // 检查资源种类清单
                if (roles[roleName].roleRcTypeList.count("*") || roles[roleName].roleRcTypeList.count(RcType)) {
                    // 检查资源名称清单
                    if (roles[roleName].roleRcNameList.empty() || roles[roleName].roleRcNameList.count(RcName))
                        return true;
                }
            }
        }
        // 然后检查用户组
        for (auto groupName: groupBelongTo) {
            if (groups.count(groupName)) {
                for (auto roleName: groups[groupName].roleList) {
                    // 检查操作清单
                    if (roles[roleName].roleOpList.count("*") || roles[roleName].roleOpList.count(opName)) {
                        // 检查资源种类清单
                        if (roles[roleName].roleRcTypeList.count("*") || roles[roleName].roleRcTypeList.count(RcType)) {
                            // 检查资源名称清单
                            if (roles[roleName].roleRcNameList.empty() || roles[roleName].roleRcNameList.count(RcName))
                                return true;
                        }
                    }
                }
            }
        }
        return false;
    }
};

map<string, UserInfo> users;// 用户

int main() {
    // freopen("./in.txt", "r", stdin);
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    cin >> n >> m >> q;
    for (int i = 1; i <= n; i++) {
        // 角色名称
        cin >> name >> nv;
        while (nv--)
            cin >> tmp, roles[name].roleOpList.emplace(tmp);
        cin >> no;
        while (no--)
            cin >> tmp, roles[name].roleRcTypeList.emplace(tmp);
        cin >> nn;
        while (nn--)
            cin >> tmp, roles[name].roleRcNameList.emplace(tmp);
    }
    for (int i = 1; i <= m; i++) {
        // 角色关联的角色名称
        cin >> name >> ns;
        while (ns--) {
            cin >> objType >> objName;
            if (objType == "u")
                users[objName].roleList.emplace(name);
            else
                groups[objName].roleList.emplace(name);
        }
    }
    for (int i = 1; i <= q; i++) {
        // 执行该操作的用户名称
        cin >> userName >> ng;
        while (ng--) {
            cin >> tmp;
            users[userName].groupBelongTo.emplace(tmp);// 用户所属的用户组
        }
        cin >> opName >> RcType >> RcName;
        cout << users[userName].authCheck(opName, RcType, RcName) << '\n';
        users[userName].groupBelongTo.clear();// ! 记得清空
    }
    return 0;
}
```
