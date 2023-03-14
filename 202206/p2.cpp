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