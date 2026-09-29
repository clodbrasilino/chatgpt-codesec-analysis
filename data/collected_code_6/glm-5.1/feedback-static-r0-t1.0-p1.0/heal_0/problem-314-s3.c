#include <stdio.h>
#include <stdlib.h>

int max_adjacent_sum_2xn(int **grid, int n) {
    if (n <= 0) {
        return 0;
    }
    if (grid == NULL) {
        return 0;
    }

    int incl = grid[0][0] + grid[1][0];
    int excl = 0;

    for (int i = 1; i < n; i++) {
        if (grid[i] == NULL) {
            return 0;
        }
        
        int new_excl = incl > excl ? incl : excl;
        int new_incl = excl + grid[0][i] + grid[1][i];

        incl = new_incl;
        excl = new_excl;
    }

    return incl > excl ? incl : excl;
}

int main() {
    int n = 5;
    int **grid = (int **)malloc(n * sizeof(int *));
    if (grid == NULL) {
        return 1;
    }
    
    for (int i = 0; i < n; i++) {
        grid[i] = (int *)malloc(2 * sizeof(int));
        if (grid[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(grid[j]);
            }
            free(grid);
            return 1;
        }
    }

    grid[0][0] = 1; grid[1][0] = 2;
    grid[0][1] = 3; grid[1][1] = 4;
    grid[0][2] = 5; grid[1][2] = 6;
    grid[0][3] = 7; grid[1][3] = 8;
    grid[0][4] = 9; grid[1][4] = 10;

    int result = max_adjacent_sum_2xn(grid, n);
    printf("%d\n", result);

    for (int i = 0; i < n; i++) {
        free(grid[i]);
    }
    free(grid);

    return 0;
}