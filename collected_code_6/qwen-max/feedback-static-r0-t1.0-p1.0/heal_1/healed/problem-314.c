#include <stdio.h>
#include <stdlib.h>

int maxSumNonAdjacent(int *grid, int n) {
    if (n == 0) return 0;
    if (n == 1) return (grid[0] > grid[1]) ? grid[0] : grid[1];

    int include = 0, exclude = 0;

    for (int i = 0; i < 2 * n; i++) {
        int newExclude = (include > exclude) ? include : exclude;
        include = exclude + grid[i];
        exclude = newExclude;
    }

    return (include > exclude) ? include : exclude;
}

int main() {
    int n;
    printf("Enter the size of the grid (2 x n): ");
    scanf("%d", &n);

    int *grid = (int *)malloc(2 * n * sizeof(int));
    if (grid == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    printf("Enter the elements of the grid: ");
    for (int i = 0; i < 2 * n; i++) {
        scanf("%d", &grid[i]);
    }

    int result = maxSumNonAdjacent(grid, n);
    printf("Maximum sum such that no two chosen numbers are adjacent: %d\n", result);

    free(grid);
    return 0;
}