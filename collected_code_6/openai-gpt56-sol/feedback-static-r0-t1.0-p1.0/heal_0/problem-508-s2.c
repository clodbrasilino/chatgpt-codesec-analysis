#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

static bool contains(const int *list, size_t length, int value)
{
    if (list == NULL) {
        return false;
    }

    for (size_t i = 0; i < length; ++i) {
        if (list[i] == value) {
            return true;
        }
    }

    return false;
}

static bool common_elements_same_order(const int *first, size_t first_length,
                                       const int *second, size_t second_length)
{
    if ((first == NULL && first_length != 0U) ||
        (second == NULL && second_length != 0U)) {
        return false;
    }

    size_t second_position = 0U;

    for (size_t i = 0U; i < first_length; ++i) {
        if (!contains(second, second_length, first[i])) {
            continue;
        }

        while (second_position < second_length &&
               second[second_position] != first[i]) {
            ++second_position;
        }

        if (second_position == second_length) {
            return false;
        }

        ++second_position;
    }

    return true;
}

int main(void)
{
    const int first[] = {3, 5, 1, 7, 9};
    const int second[] = {8, 5, 2, 1, 4, 7};
    const size_t first_length = sizeof(first) / sizeof(first[0]);
    const size_t second_length = sizeof(second) / sizeof(second[0]);

    const bool result = common_elements_same_order(
        first, first_length, second, second_length
    );

    if (printf("%s\n", result ? "Same order" : "Different order") < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}