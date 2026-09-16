#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

bool sum_column(const int *const *lists,
                const size_t *lengths,
                size_t list_count,
                size_t column,
                int64_t *result)
{
    int64_t total = 0;

    if (result == NULL) {
        return false;
    }

    *result = 0;

    if (list_count > 0 && (lists == NULL || lengths == NULL)) {
        return false;
    }

    for (size_t i = 0; i < list_count; ++i) {
        int64_t value;

        if (lists[i] == NULL || column >= lengths[i]) {
            return false;
        }

        value = lists[i][column];

        if ((value > 0 && total > INT64_MAX - value) ||
            (value < 0 && total < INT64_MIN - value)) {
            return false;
        }

        total += value;
    }

    *result = total;
    return true;
}

int main(void)
{
    const int first[] = {1, 2, 3};
    const int second[] = {4, 5, 6};
    const int third[] = {7, 8, 9};
    const int *lists[] = {first, second, third};
    const size_t lengths[] = {
        sizeof first / sizeof first[0],
        sizeof second / sizeof second[0],
        sizeof third / sizeof third[0]
    };
    const size_t column = 1;
    int64_t result;

    if (!sum_column(lists,
                    lengths,
                    sizeof lists / sizeof lists[0],
                    column,
                    &result)) {
        fputs("Unable to sum the requested column.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRId64 "\n", result);
    return EXIT_SUCCESS;
}