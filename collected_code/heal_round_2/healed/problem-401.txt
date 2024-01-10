#include <stdio.h>

void tupleAddition(int len, const int tuple1[][2], const int tuple2[][2], int result[][2]) {
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < 2; j++) {
            result[i][j] = tuple1[i][j] + tuple2[i][j];
        }
    }
}

int main(){
    const int tuple1[][2] = {{1, 2}, {3, 4}, {5, 6}};
    const int tuple2[][2] = {{7, 8}, {9, 10}, {11, 12}};
    int len = sizeof(tuple1) / sizeof(tuple1[0]);

    int result[len][2];
    tupleAddition(len, tuple1, tuple2, result);

    for (int i = 0; i < len; i++) {
        for (int j = 0; j < 2; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }

    return 0;
}