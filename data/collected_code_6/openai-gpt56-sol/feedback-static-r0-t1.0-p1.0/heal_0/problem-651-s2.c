#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

static bool tuple_is_subset(const int *subset, size_t subset_size,
                            const int *tuple, size_t tuple_size)
{
    if ((subset == NULL && subset_size != 0U) ||
        (tuple == NULL && tuple_size != 0U)) {
        return false;
    }

    for (size_t i = 0U; i < subset_size; ++i) {
        size_t subset_count = 0U;
        size_t tuple_count = 0U;
        bool already_counted = false;

        for (size_t j = 0U; j < i; ++j) {
            if (subset[j] == subset[i]) {
                already_counted = true;
                break;
            }
        }

        if (already_counted) {
            continue;
        }

        for (size_t j = 0U; j < subset_size; ++j) {
            if (subset[j] == subset[i]) {
                ++subset_count;
            }
        }

        for (size_t j = 0U; j < tuple_size; ++j) {
            if (tuple[j] == subset[i]) {
                ++tuple_count;
            }
        }

        if (subset_count > tuple_count) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    const int subset[] = {2, 3, 3};
    const int tuple[] = {1, 2, 3, 3, 4};

    const bool result = tuple_is_subset(
        subset,
        sizeof subset / sizeof subset[0],
        tuple,
        sizeof tuple / sizeof tuple[0]
    );

    if (printf("%s\n", result ? "true" : "false") < 0) {
        return 1;
    }

    return 0;
}