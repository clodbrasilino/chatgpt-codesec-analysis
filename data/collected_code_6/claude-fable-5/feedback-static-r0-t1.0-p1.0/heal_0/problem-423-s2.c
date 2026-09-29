#include <stdio.h>
#include <stdlib.h>

static int max_of_three(int a, int b, int c)
{
    int m = a;
    if (b > m) {
        m = b;
    }
    if (c > m) {
        m = c;
    }
    return m;
}

static int get_gold_max(const int *mine, int rows, int cols)
{
    int **table;
    int i;
    int j;
    int result;

    if ((mine == NULL) || (rows <= 0) || (cols <= 0)) {
        return -1;
    }

    table = (int **)malloc((size_t)rows * sizeof(int *));
    if (table == NULL) {
        return -1;
    }

    for (i = 0; i < rows; i++) {
        table[i] = (int *)malloc((size_t)cols * sizeof(int));
        if (table[i] == NULL) {
            for (j = 0; j < i; j++) {
                free(table[j]);
            }
            free(table);
            return -1;
        }
    }

    for (i = 0; i < rows; i++) {
        table[i][cols - 1] = mine[(i * cols) + (cols - 1)];
    }

    for (j = cols - 2; j >= 0; j--) {
        for (i = 0; i < rows; i++) {
            int right = table[i][j + 1];
            int right_up = (i > 0) ? table[i - 1][j + 1] : 0;
            int right_down = (i < rows - 1) ? table[i + 1][j + 1] : 0;
            table[i][j] = mine[(i * cols) + j] + max_of_three(right, right_up, right_down);
        }
    }

    result = table[0][0];
    for (i = 1; i < rows; i++) {
        if (table[i][0] > result) {
            result = table[i][0];
        }
    }

    for (i = 0; i < rows; i++) {
        free(table[i]);
    }
    free(table);

    return result;
}

int main(void)
{
    int mine[4][4] = {
        {1, 3, 1, 5},
        {2, 2, 4, 1},
        {5, 0, 2, 3},
        {0, 6, 1, 2}
    };
    int result;

    result = get_gold_max(&mine[0][0], 4, 4);
    if (result < 0) {
        fprintf(stderr, "Error computing maximum gold\n");
        return EXIT_FAILURE;
    }

    if (printf("Maximum gold collected: %d\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}