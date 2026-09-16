#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TUPLE_COUNT 4
#define TUPLE_SIZE 2

static int index_wise_addition(const int a[][TUPLE_SIZE], const int b[][TUPLE_SIZE],
                               int result[][TUPLE_SIZE], size_t count, size_t size)
{
    size_t i;
    size_t j;

    if ((a == NULL) || (b == NULL) || (result == NULL)) {
        return -1;
    }

    if ((count == 0U) || (size == 0U)) {
        return -1;
    }

    for (i = 0U; i < count; i++) {
        for (j = 0U; j < size; j++) {
            long sum = (long)a[i][j] + (long)b[i][j];
            if ((sum > (long)INT_MAX) || (sum < (long)INT_MIN)) {
                return -1;
            }
            result[i][j] = (int)sum;
        }
    }

    return 0;
}

int main(void)
{
    int tuple1[TUPLE_COUNT][TUPLE_SIZE] = {
        {1, 3},
        {4, 5},
        {2, 9},
        {1, 10}
    };

    int tuple2[TUPLE_COUNT][TUPLE_SIZE] = {
        {6, 7},
        {3, 9},
        {1, 1},
        {7, 3}
    };

    int result[TUPLE_COUNT][TUPLE_SIZE] = { {0, 0}, {0, 0}, {0, 0}, {0, 0} };
    size_t i;
    int status;

    status = index_wise_addition(tuple1, tuple2, result, (size_t)TUPLE_COUNT, (size_t)TUPLE_SIZE);

    if (status != 0) {
        (void)fprintf(stderr, "Error: addition failed\n");
        return EXIT_FAILURE;
    }

    (void)printf("(");
    for (i = 0U; i < (size_t)TUPLE_COUNT; i++) {
        (void)printf("(%d, %d)", result[i][0], result[i][1]);
        if (i < ((size_t)TUPLE_COUNT - 1U)) {
            (void)printf(", ");
        }
    }
    (void)printf(")\n");

    return EXIT_SUCCESS;
}