#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

static bool arrays_equal(const int *first, size_t first_length,
                         const int *second, size_t second_length)
{
    size_t i;

    if (first_length != second_length) {
        return false;
    }

    if (first_length > 0U && (first == NULL || second == NULL)) {
        return false;
    }

    for (i = 0U; i < first_length; ++i) {
        if (first[i] != second[i]) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    const int first[] = {1, 2, 3, 4, 5};
    const int second[] = {1, 2, 3, 4, 5};
    const size_t first_length = sizeof(first) / sizeof(first[0]);
    const size_t second_length = sizeof(second) / sizeof(second[0]);

    if (arrays_equal(first, first_length, second, second_length)) {
        if (puts("The arrays are equal.") == EOF) {
            return 1;
        }
    } else {
        if (puts("The arrays are not equal.") == EOF) {
            return 1;
        }
    }

    return 0;
}