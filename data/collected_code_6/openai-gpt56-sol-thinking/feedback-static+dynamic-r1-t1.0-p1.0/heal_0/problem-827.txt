#include <stdbool.h>
#include <stddef.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

bool sum_column(const int *const *lists,
                const size_t *lengths,
                size_t list_count,
                size_t column,
                long long *result)
{
    long long sum = 0;

    if (result == NULL) {
        return false;
    }

    *result = 0;

    if (list_count > 0 && (lists == NULL || lengths == NULL)) {
        return false;
    }

    for (size_t i = 0; i < list_count; ++i) {
        long long value;

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
    const int first[] = {1, 2, 3};
    const int second[] = {4, 5, 6};
    const int third[] = {7, 8, 9};
    const int *const lists[] = {first, second, third};
    const size_t lengths[] = {
        sizeof(first) / sizeof(first[0]),
        sizeof(second) / sizeof(second[0]),
        sizeof(third) / sizeof(third[0])
    };
    const size_t column = 1;
    long long result;

    if (!sum_column(lists,
                    lengths,
                    sizeof(lists) / sizeof(lists[0]),
                    column,
                    &result)) {
        return EXIT_FAILURE;
    }

    if (printf("%lld\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}