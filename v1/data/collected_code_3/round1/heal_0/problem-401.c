#include <stdio.h>

#define SIZE 3

void add_tuples(int tuple1[][SIZE], int tuple2[][SIZE], int m, int n) {
    int i, j;
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            tuple1[i][j] = tuple1[i][j] + tuple2[i][j];
        }
    }
}

int main() {
    int tuple1[2][SIZE] = {{1, 2, 3}, {4, 5, 6}};
    int tuple2[2][SIZE] = {{7, 8, 9}, {10, 11, 12}};
    int m = sizeof(tuple1) / sizeof(tuple1[0]);
    int n = sizeof(tuple1[0]) / sizeof(tuple1[0][0]);

    add_tuples(tuple1, tuple2, m, n);

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", tuple1[i][j]);
        }
        printf("\n");
    }

    return 0;
}