#include <stdio.h>
#include <stdlib.h>

#define ROWS 5
#define COLS 3

static int compare_second(const void *a, const void *b)
{
    const int *row_a = (const int *)a;
    const int *row_b = (const int *)b;

    if (row_a[1] < row_b[1]) {
        return -1;
    }
    if (row_a[1] > row_b[1]) {
        return 1;
    }
    return 0;
}

static int sort_by_second(int list[][COLS], size_t rows)
{
    if (list == NULL || rows == 0U) {
        return -1;
    }
    qsort(list, rows, sizeof(list[0]), compare_second);
    return 0;
}

static void print_list(const int list[][COLS], size_t rows)
{
    size_t i;
    size_t j;

    if (list == NULL) {
        return;
    }

    for (i = 0U; i < rows; i++) {
        (void)printf("[");
        for (j = 0U; j < (size_t)COLS; j++) {
            (void)printf("%d", list[i][j]);
            if (j < (size_t)(COLS - 1)) {
                (void)printf(", ");
            }
        }
        (void)printf("]\n");
    }
}

int main(void)
{
    int list[ROWS][COLS] = {
        {1, 9, 3},
        {4, 2, 6},
        {7, 5, 8},
        {0, 1, 2},
        {3, 7, 5}
    };

    if (sort_by_second(list, (size_t)ROWS) != 0) {
        (void)fprintf(stderr, "Failed to sort list\n");
        return EXIT_FAILURE;
    }

    print_list(list, (size_t)ROWS);

    return EXIT_SUCCESS;
}