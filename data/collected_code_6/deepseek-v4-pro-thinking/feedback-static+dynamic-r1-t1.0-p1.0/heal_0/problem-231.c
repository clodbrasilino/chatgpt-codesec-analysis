#include <stdio.h>
#include <stdlib.h>

int maxPathSum(int **triangle, int rows)
{
    for (int r = rows - 2; r >= 0; r--) {
        for (int c = 0; c <= r; c++) {
            int left = triangle[r + 1][c];
            int right = triangle[r + 1][c + 1];
            triangle[r][c] += (left > right) ? left : right;
        }
    }
    return triangle[0][0];
}

int main(void)
{
    int rows;

    if (scanf("%d", &rows) != 1 || rows <= 0) {
        return EXIT_FAILURE;
    }

    int **triangle = malloc((size_t)rows * sizeof(*triangle));
    if (triangle == NULL) {
        return EXIT_FAILURE;
    }

    for (int i = 0; i < rows; i++) {
        triangle[i] = malloc((size_t)(i + 1) * sizeof(*triangle[i]));
        if (triangle[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(triangle[j]);
            }
            free(triangle);
            return EXIT_FAILURE;
        }

        for (int j = 0; j <= i; j++) {
            if (scanf("%d", &triangle[i][j]) != 1) {
                for (int k = 0; k <= i; k++) {
                    free(triangle[k]);
                }
                free(triangle);
                return EXIT_FAILURE;
            }
        }
    }

    int result = maxPathSum(triangle, rows);
    printf("%d\n", result);

    for (int i = 0; i < rows; i++) {
        free(triangle[i]);
    }
    free(triangle);

    return EXIT_SUCCESS;
}