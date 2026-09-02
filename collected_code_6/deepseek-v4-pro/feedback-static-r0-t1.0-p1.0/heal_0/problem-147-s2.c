#include <stdio.h>
#include <stdlib.h>

int max_path_sum(int **triangle, int rows) {
    if (triangle == NULL || rows <= 0) {
        return 0;
    }

    if (rows == 1) {
        return triangle[0][0];
    }

    int dp_prev[rows];
    int dp_curr[rows];

    dp_prev[0] = triangle[0][0];

    for (int i = 1; i < rows; i++) {
        dp_curr[0] = dp_prev[0] + triangle[i][0];
        dp_curr[i] = dp_prev[i - 1] + triangle[i][i];

        for (int j = 1; j < i; j++) {
            int left = dp_prev[j - 1];
            int right = dp_prev[j];
            dp_curr[j] = (left > right ? left : right) + triangle[i][j];
        }

        for (int j = 0; j <= i; j++) {
            dp_prev[j] = dp_curr[j];
        }
    }

    int max_sum = dp_prev[0];
    for (int j = 1; j < rows; j++) {
        if (dp_prev[j] > max_sum) {
            max_sum = dp_prev[j];
        }
    }

    return max_sum;
}

int main() {
    int rows = 4;
    int **triangle = malloc(rows * sizeof(int *));
    if (triangle == NULL) {
        return 1;
    }

    triangle[0] = malloc(1 * sizeof(int));
    triangle[1] = malloc(2 * sizeof(int));
    triangle[2] = malloc(3 * sizeof(int));
    triangle[3] = malloc(4 * sizeof(int));

    if (triangle[0] == NULL || triangle[1] == NULL || 
        triangle[2] == NULL || triangle[3] == NULL) {
        for (int i = 0; i < rows; i++) {
            free(triangle[i]);
        }
        free(triangle);
        return 1;
    }

    triangle[0][0] = 3;
    triangle[1][0] = 7;
    triangle[1][1] = 4;
    triangle[2][0] = 2;
    triangle[2][1] = 4;
    triangle[2][2] = 6;
    triangle[3][0] = 8;
    triangle[3][1] = 5;
    triangle[3][2] = 9;
    triangle[3][3] = 3;

    int result = max_path_sum(triangle, rows);
    printf("%d\n", result);

    for (int i = 0; i < rows; i++) {
        free(triangle[i]);
    }
    free(triangle);

    return 0;
}