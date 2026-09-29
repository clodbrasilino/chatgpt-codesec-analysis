#include <stdio.h>
#include <stdlib.h>

#define ROWS 4
#define COLS 2

int add_nested_tuples(const int a[][COLS], const int b[][COLS],
                      int result[][COLS], size_t rows, size_t cols)
{
    size_t i;
    size_t j;

    if ((a == NULL) || (b == NULL) || (result == NULL)) {
        return -1;
    }

    if ((rows == 0U) || (cols == 0U) || (cols > COLS)) {
        return -1;
    }

    for (i = 0U; i < rows; i++) {
        for (j = 0U; j < cols; j++) {
            long sum = (long)a[i][j] + (long)b[i][j];
            if ((sum > 2147483647L) || (sum < -2147483648L)) {
                return -1;
            }
            result[i][j] = (int)sum;
        }
    }

    return 0;
}

int main(void)
{
    const int tuple1[ROWS][COLS] = {
        {1, 3},
        {4, 5},
        {2, 9},
        {1, 10}
    };
    const int tuple2[ROWS][COLS] = {
        {6, 7},
        {3, 9},
        {1, 1},
        {7, 3}
    };
    int result[ROWS][COLS];
    size_t i;
    size_t j;
    int status;

    status = add_nested_tuples(tuple1, tuple2, result, ROWS, COLS);
    if (status != 0) {
        (void)fprintf(stderr, "Error: addition failed\n");
        return EXIT_FAILURE;
    }

    (void)printf("Result:\n");
    for (i = 0U; i < ROWS; i++) {
        (void)printf("(");
        for (j = 0U; j < COLS; j++) {
            if (j > 0U) {
                (void)printf(", ");
            }
            (void)printf("%d", result[i][j]);
        }
        (void)printf(")\n");
    }

    return EXIT_SUCCESS;
}