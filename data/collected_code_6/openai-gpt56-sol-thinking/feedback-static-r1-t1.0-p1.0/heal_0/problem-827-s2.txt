#include <stdbool.h>
#include <stddef.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

bool sum_column(const int *const lists[],
                const size_t lengths[],
                size_t list_count,
                size_t column,
                long long *result)
{
    long long sum = 0;

    if (result == NULL ||
        (list_count > 0 && (lists == NULL || lengths == NULL))) {
        return false;
    }

    for (size_t i = 0; i < list_count; ++i) {
        int value;

        if (lists[i] == NULL || column >= lengths[i]) {
            return false;
        }

        value = lists[i][column];

        if ((value > 0 && sum > LLONG_MAX - value) ||
            (value < 0 && sum < LLONG_MIN - value)) {
            return false;
        }

        sum += value;
    }

    *result = sum;
    return true;
}

int main(void)
{
    const int row1[] = {1, 2, 3, 4};
    const int row2[] = {5, 6, 7, 8};
    const int row3[] = {9, 10, 11, 12};
    const int *const lists[] = {row1, row2, row3};
    const size_t lengths[] = {
        sizeof row1 / sizeof row1[0],
        sizeof row2 / sizeof row2[0],
        sizeof row3 / sizeof row3[0]
    };
    const size_t column = 2;
    long long sum;

    if (!sum_column(lists,
                    lengths,
                    sizeof lists / sizeof lists[0],
                    column,
                    &sum)) {
        fputs("Unable to sum the requested column.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%lld\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}