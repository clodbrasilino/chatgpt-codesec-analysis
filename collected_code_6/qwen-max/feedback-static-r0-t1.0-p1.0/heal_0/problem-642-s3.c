#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROWS 5
#define COLS 3

typedef int Tuple[COLS];

int compareTuples(const void *a, const void *b) {
    return memcmp(a, b, sizeof(Tuple));
}

int isUnique(Tuple matrix[], int index, int n) {
    for (int i = 0; i < index; i++) {
        if (compareTuples(matrix + i, matrix + index) == 0) {
            return 0;
        }
    }
    return 1;
}

void removeSimilarRows(Tuple matrix[], int *n) {
    Tuple temp[ROWS];
    int count = 0;

    for (int i = 0; i < *n; i++) {
        if (isUnique(matrix, i, *n)) {
            memcpy(temp + count, matrix + i, sizeof(Tuple));
            count++;
        }
    }

    memcpy(matrix, temp, count * sizeof(Tuple));
    *n = count;
}

int main() {
    Tuple matrix[ROWS] = {
        {1, 2, 3},
        {4, 5, 6},
        {1, 2, 3},
        {7, 8, 9},
        {4, 5, 6}
    };

    int n = ROWS;

    removeSimilarRows(matrix, &n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}