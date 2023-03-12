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