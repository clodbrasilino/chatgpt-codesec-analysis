#include <stdio.h>

void tupleAddition(int tuple1[][2], int tuple2[][2], int len) {
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < 2; j++) {
            tuple1[i][j] += tuple2[i][j];
        }
    }
}

int main() {
    int tuple1[][2] = {{1, 2}, {3, 4}, {5, 6}};
    int tuple2[][2] = {{7, 8}, {9, 10}, {11, 12}};
    int len = sizeof(tuple1) / sizeof(tuple1[0]);

    tupleAddition(tuple1, tuple2, len);

    for (int i = 0; i < len; i++) {
        for (int j = 0; j < 2; j++) {
            printf("%d ", tuple1[i][j]);
        }
        printf("\n");
    }

    return 0;
}