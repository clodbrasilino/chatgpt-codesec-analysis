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
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000011,time:5034,execs:4625,op:havoc,rep:1; likely memory-safety defect
  */

int main() {
    int n;
    printf("Enter the size of the grid (2 x n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid grid size\n");
        exit(EXIT_FAILURE);
    }

    int *grid = (int *)malloc(2 * n * sizeof(int));
    if (grid == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    printf("Enter the elements of the grid: ");
    for (int i = 0; i < 2 * n; i++) {
        if (scanf("%d", &grid[i]) != 1) {
            fprintf(stderr, "Input error\n");
            free(grid);
            exit(EXIT_FAILURE);
        }
    }

    if (n == 0) {
        free(grid);
        return 0;
    }

    int result = maxSumNonAdjacent(grid, n);
    printf("Maximum sum such that no two chosen numbers are adjacent: %d\n", result);

    free(grid);
    return 0;
}