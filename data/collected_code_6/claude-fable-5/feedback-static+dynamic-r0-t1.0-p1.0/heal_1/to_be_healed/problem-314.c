#include <stdio.h>
#include <stdlib.h>

static int max_int(int a, int b)
{
    return (a > b) ? a : b;
}

static int max_sum_no_adjacent(const int grid[2][100], int n)
{
    int incl;
    int excl;
    int i;
    /* Possible weaknesses found:
     *  The scope of the variable 'current' can be reduced. [variableScope]
     */
    int current;
    /* Possible weaknesses found:
     *  The scope of the variable 'new_excl' can be reduced. [variableScope]
     */
    int new_excl;

    if (n <= 0) {
        return 0;
    }

    incl = max_int(grid[0][0], grid[1][0]);
    excl = 0;

    for (i = 1; i < n; i++) {
        current = max_int(grid[0][i], grid[1][i]);
        new_excl = max_int(incl, excl);
        incl = excl + current;
        excl = new_excl;
    }

    return max_int(incl, excl);
}

int main(void)
{
    int grid[2][100];
    int n;
    int i;
    int j;
    int result;

    printf("Enter number of columns (1 to 100): ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    if (n < 1 || n > 100) {
        fprintf(stderr, "Error: number of columns out of range\n");
        return EXIT_FAILURE;
    }

    printf("Enter grid values row by row:\n");
    for (i = 0; i < 2; i++) {
        for (j = 0; j < n; j++) {
            if (scanf("%d", &grid[i][j]) != 1) {
                fprintf(stderr, "Error: invalid grid value\n");
                return EXIT_FAILURE;
            }
        }
    }

    result = max_sum_no_adjacent((const int (*)[100])grid, n);
    printf("Maximum sum with no two adjacent numbers: %d\n", result);

    return EXIT_SUCCESS;
}