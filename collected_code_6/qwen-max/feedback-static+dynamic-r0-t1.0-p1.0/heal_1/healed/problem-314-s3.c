#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int findMaxSum(int** grid, int n) {
    if (n == 0) return 0;
    if (n == 1) return max(grid[0][0], grid[1][0]);

    int incl = max(grid[0][0], grid[1][0]);
    int excl = 0;

    for (int i = 1; i < n; i++) {
        int excl_new = max(excl, incl);
        incl = excl + max(grid[0][i], grid[1][i]);
        excl = excl_new;
    }

    return max(incl, excl);
}

int main() {
    int n;
    printf("Enter the number of columns: ");
    if (scanf("%d", &n) != 1 || n < 0) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    int** grid = (int**)malloc(2 * sizeof(int*));
    if (grid == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    for (int i = 0; i < 2; i++) {
        grid[i] = (int*)malloc(n * sizeof(int));
        if (grid[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            for (int j = 0; j < i; j++) {
                free(grid[j]);
            }
            free(grid);
            return 1;
        }
    }

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < n; j++) {
            printf("Enter element for row %d, column %d: ", i, j);
            if (scanf("%d", &grid[i][j]) != 1) {
                fprintf(stderr, "Invalid input\n");
                for (int k = 0; k < 2; k++) {
                    free(grid[k]);
                }
                free(grid);
                return 1;
            }
        }
    }

    int result = findMaxSum(grid, n);
    printf("Maximum sum such that no two chosen numbers are adjacent: %d\n", result);

    for (int i = 0; i < 2; i++) {
        free(grid[i]);
    }
    free(grid);

    return 0;
}