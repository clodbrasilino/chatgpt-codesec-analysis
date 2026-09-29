#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

static bool arrays_equal(const int *first, size_t first_length,
                         const int *second, size_t second_length)
{
    if (first_length != second_length) {
        return false;
    }

    if (first_length == 0U) {
        return true;
    }

    if (first == NULL || second == NULL) {
        return false;
    }

    for (size_t first_index = 0U, second_index = 0U;
         first_index < first_length && second_index < second_length;
         ++first_index, ++second_index) {
        if (first[first_index] != second[second_index]) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    const int first[] = {1, 2, 3, 4, 5};
    const int second[] = {1, 2, 3, 4, 5};
    const size_t first_length = sizeof first / sizeof first[0];
    const size_t second_length = sizeof second / sizeof second[0];

    const bool equal =
        arrays_equal(first, first_length, second, second_length);

    if (printf("The arrays are %s.\n", equal ? "equal" : "not equal") < 0) {
        return 1;
    }

    return 0;
}