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
    const int *first_end = first + first_length;
    const int *second_end = second + second_length;

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

    /* Possible weaknesses found:
     * Flawfinder equal: Function does not check the second iterator for over-read conditions (CWE-126). This function is often discouraged by most C++ coding standards in favor of its safer alternatives provided since C++14. Consider using a form of this function that checks the second iterator before potentially overflowing it. (risk 1, buffer)
     */
    if (printf("Arrays are %s.\n", equal ? "equal" : "not equal") < 0) {
        return 1;
    }

    return 0;
}