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
        bool found = false;

        for (size_t j = 0U; j < tuple_size; ++j) {
            if (subset[i] == tuple[j]) {
                found = true;
                break;
            }
        }

        if (!found) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    const int tuple1[] = {2, 4};
    const int tuple2[] = {1, 2, 3, 4, 5};
    const size_t tuple1_size = sizeof tuple1 / sizeof tuple1[0];
    const size_t tuple2_size = sizeof tuple2 / sizeof tuple2[0];

    if (tuple_is_subset(tuple1, tuple1_size, tuple2, tuple2_size)) {
        if (puts("tuple1 is a subset of tuple2") == EOF) {
            return 1;
        }
    } else {
        if (puts("tuple1 is not a subset of tuple2") == EOF) {
            return 1;
        }
    }

    return 0;
}