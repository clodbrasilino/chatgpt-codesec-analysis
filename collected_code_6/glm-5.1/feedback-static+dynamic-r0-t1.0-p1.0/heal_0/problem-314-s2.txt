#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return a > b ? a : b;
}

int max_non_adjacent_sum(int** grid, int n) {
    if (n <= 0) {
        return 0;
    }
    if (grid == NULL) {
        return 0;
    }
    int incl = max(grid[0][0], grid[1][0]);
    int excl = 0;
    int excl_new;
    for (int i = 1; i < n; i++) {
        if (grid[0] == NULL || grid[1] == NULL) {
            return 0;
        }
        excl_new = max(incl, excl);
        int current_max = max(grid[0][i], grid[1][i]);
        incl = excl + current_max;
        excl = excl_new;
    }
    return max(incl, excl);
}

int main(void) {
    int n = 5;
    int row1[] = {1, 2, 3, 4, 5};
    int row2[] = {6, 7, 8, 9, 10};
    int* grid[2];
    grid[0] = row1;
    grid[1] = row2;
    int result = max_non_adjacent_sum(grid, n);
    printf("%d\n", result);
    return 0;
}