#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

static bool contains(const int array[], size_t length, int value)
{
    for (size_t i = 0; i < length; ++i) {
        if (array[i] == value) {
            return true;
        }
    }

    return false;
}

static bool common_elements_same_order(const int first[], size_t first_length,
                                       const int second[], size_t second_length)
{
    size_t second_position = 0;

    if ((first == NULL && first_length != 0U) ||
        (second == NULL && second_length != 0U)) {
        return false;
    }

    for (size_t i = 0; i < first_length; ++i) {
        if (!contains(second, second_length, first[i])) {
            continue;
        }

        while (second_position < second_length &&
               second[second_position] != first[i]) {
            if (contains(first, first_length, second[second_position])) {
                return false;
            }
            ++second_position;
        }

        if (second_position == second_length) {
            return false;
        }

        ++second_position;
    }

    while (second_position < second_length) {
        if (contains(first, first_length, second[second_position])) {
            return false;
        }
        ++second_position;
    }

    return true;
}

int main(void)
{
    const int first[] = {1, 2, 3, 4, 5, 6};
    const int second[] = {8, 2, 9, 4, 6, 10};
    const size_t first_length = sizeof first / sizeof first[0];
    const size_t second_length = sizeof second / sizeof second[0];

    if (common_elements_same_order(first, first_length,
                                   second, second_length)) {
        if (puts("The common elements are in the same order.") == EOF) {
            return 1;
        }
    } else {
        if (puts("The common elements are not in the same order.") == EOF) {
            return 1;
        }
    }

    return 0;
}