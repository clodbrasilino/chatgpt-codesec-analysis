#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int maxSumNoAdjacent(int** grid, int n) {
    if (grid == NULL || n <= 0) {
        return 0;
    }

    int inc = max(grid[0][0], grid[1][0]);
    int exc = 0;
    int exc_new;

    for (int i = 1; i < n; i++) {
        exc_new = max(inc, exc);
        inc = exc + max(grid[0][i], grid[1][i]);
        exc = exc_new;
    }

    return max(inc, exc);
}

int main(void) {
    int n = 5;
    
    int** grid = (int**)malloc(2 * sizeof(int*));
    if (grid == NULL) {
        return EXIT_FAILURE;
    }
    
    for (int i = 0; i < 2; i++) {
        grid[i] = (int*)malloc(n * sizeof(int));
        if (grid[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(grid[j]);
            }
            free(grid);
            return EXIT_FAILURE;
        }
    }

    int row1[] = {1, 4, 5, 3, 2};
    int row2[] = {2, 5, 1, 9, 6};

    for (int i = 0; i < n; i++) {
        grid[0][i] = row1[i];
        grid[1][i] = row2[i];
    }

    int result = maxSumNoAdjacent(grid, n);
    printf("%d\n", result);

    for (int i = 0; i < 2; i++) {
        free(grid[i]);
    }
    free(grid);

    return EXIT_SUCCESS;
}