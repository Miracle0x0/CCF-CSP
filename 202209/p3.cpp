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