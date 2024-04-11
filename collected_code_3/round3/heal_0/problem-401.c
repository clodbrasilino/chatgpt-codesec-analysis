#include <stdio.h>

#define SIZE 5

void add_tuples(int tuple1[][SIZE], int tuple2[][SIZE], int rows, int result[][SIZE]) {
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < SIZE; j++) {
            result[i][j] = tuple1[i][j] + tuple2[i][j];
        }
    }
}

int main() {
    int tuple1[2][SIZE] = {{1, 2, 3, 4, 5}, {6, 7, 8, 9, 10}};
    int tuple2[2][SIZE] = {{11, 12, 13, 14, 15}, {16, 17, 18, 19, 20}};
    int result[2][SIZE];

    add_tuples(tuple1, tuple2, 2, result);

    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < SIZE; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }

    return 0;
}