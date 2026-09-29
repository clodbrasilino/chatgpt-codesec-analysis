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

    const int *first_current = first;
    const int *second_current = second;
    const int *const first_end = first + first_length;
    const int *const second_end = second + second_length;

    while (first_current != first_end && second_current != second_end) {
        if (*first_current != *second_current) {
            return false;
        }

        ++first_current;
        ++second_current;
    }

    return first_current == first_end && second_current == second_end;
}

int main(void)
{
    const int first[] = {1, 2, 3, 4, 5};
    const int second[] = {1, 2, 3, 4, 5};

    const size_t first_length = sizeof first / sizeof first[0];
    const size_t second_length = sizeof second / sizeof second[0];

    const bool equal = arrays_equal(first, first_length,
                                    second, second_length);

    if (printf("The arrays are %s.\n",
               equal ? "equal" : "not equal") < 0) {
        return 1;
    }

    return 0;
}