#include <stdio.h>
#include <stdlib.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

int minTotal(int **triangle, int numRows) {
    for (int i = numRows - 2; i >= 0; --i) {
        for (int j = 0; j <= i; ++j) {
            triangle[i][j] += MIN(triangle[i + 1][j], triangle[i + 1][j + 1]);
        }
    }

    return triangle[0][0];
}

int main() {
    int numRows = 4;
    int **triangle = (int **)malloc(numRows * sizeof(int *));
    if (triangle == NULL) {
        return -1;
    }

    for (int i = 0; i < numRows; ++i) {
        triangle[i] = (int *)malloc((i + 1) * sizeof(int));
        if (triangle[i] == NULL) {
            while(i-- > 0) {
                free(triangle[i]);
            }
            free(triangle);
            return -1;
        }
    }

    triangle[0][0] = 2;
    triangle[1][0] = 3;
    triangle[1][1] = 4;
    triangle[2][0] = 6;
    triangle[2][1] = 5;
    triangle[2][2] = 7;
    triangle[3][0] = 4;
    triangle[3][1] = 1;
    triangle[3][2] = 8;
    triangle[3][3] = 3;

    printf("Minimum Total: %d\n", minTotal(triangle, numRows));

    for (int i = 0; i < numRows; ++i) {
        free(triangle[i]);
    }
    free(triangle);

    return 0;
}