#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

int maxPathSum(int tri[3][3], int m, int n) {
    for (int i = m - 1; i >= 0; i--) {
        for (int j = 0; j <= i; j++) {
            if (tri[i + 1][j] > tri[i + 1][j + 1])
                tri[i][j] += tri[i + 1][j];
            else
                tri[i][j] += tri[i + 1][j + 1];
        }
    }
    return tri[0][0];
}

int main() {
    int tri[3][3] = { {1, 0, 0},
                      {4, 8, 0},
                      {1, 5, 3} };
    printf("%d\n", maxPathSum(tri, 2, 2));
    return 0;
}