#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

static bool tuple_contains_all_valid_values(const int tuple[],
                                            size_t tuple_size,
                                            const int valid_values[],
                                            size_t valid_count)
{
    size_t i;
    size_t j;

    if ((tuple == NULL && tuple_size != 0U) ||
        (valid_values == NULL && valid_count != 0U)) {
        return false;
    }

    for (i = 0U; i < valid_count; ++i) {
        bool found = false;

        for (j = 0U; j < tuple_size; ++j) {
            if (tuple[j] == valid_values[i]) {
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
    const int tuple[] = {4, 1, 3, 2};
    const int valid_values[] = {1, 2, 3, 4};
    const size_t tuple_size = sizeof tuple / sizeof tuple[0];
    const size_t valid_count = sizeof valid_values / sizeof valid_values[0];

    if (tuple_contains_all_valid_values(tuple, tuple_size,
                                        valid_values, valid_count)) {
        if (puts("The tuple contains all valid values.") == EOF) {
            return 1;
        }
    } else {
        if (puts("The tuple does not contain all valid values.") == EOF) {
            return 1;
        }
    }

    return 0;
}