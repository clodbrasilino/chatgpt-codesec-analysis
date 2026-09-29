#include <stdio.h>
#include <stdlib.h>

int eulerian(int n, int m) {
    int a[n + 1][m + 1];
    for (int i = 0; i <= n; i++) {
        a[i][0] = 1;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (i < j) {
                a[i][j] = 0;
            } else {
                a[i][j] = (i - j) * a[i - 1][j - 1] + (j + 1) * a[i - 1][j];
            }
        }
    }
    return a[n][m];
}

int main() {
    int n = 4;
    int m = 2;
    printf("Eulerian number A(%d, %d) is %d\n", n, m, eulerian(n, m));
    return 0;
}