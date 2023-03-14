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

// 用户组信息
class GroupInfo {
public:
    set<string> roleList;// 所属的角色
};

map<string, RoleInfo> roles;  // 角色
map<string, UserInfo> users;  // 用户
map<string, GroupInfo> groups;// 用户组

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