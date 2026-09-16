#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

static bool contains(const int values[], size_t length, int target)
{
    for (size_t i = 0; i < length; ++i) {
        if (values[i] == target) {
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
    const int first[] = {1, 2, 3, 4, 5};
    const int second[] = {7, 2, 8, 4, 9, 5};
    const size_t first_length = sizeof(first) / sizeof(first[0]);
    const size_t second_length = sizeof(second) / sizeof(second[0]);

    printf("%s\n",
           common_elements_same_order(first, first_length,
                                      second, second_length)
               ? "The common elements are in the same order."
               : "The common elements are not in the same order.");

    return 0;
}