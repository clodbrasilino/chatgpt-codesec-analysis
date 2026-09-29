#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

static bool find_second_smallest(const int *values, size_t count, int *result)
{
    int smallest;
    int second_smallest;
    bool has_second = false;

    if (values == NULL || result == NULL || count < 2U) {
        return false;
    }

    smallest = values[0];

    for (size_t i = 1U; i < count; ++i) {
        if (values[i] < smallest) {
            second_smallest = smallest;
            smallest = values[i];
            has_second = true;
        } else if (values[i] > smallest &&
                   (!has_second || values[i] < second_smallest)) {
            second_smallest = values[i];
            has_second = true;
        }
    }

    if (!has_second) {
        return false;
    }

    *result = second_smallest;
    return true;
}

int main(void)
{
    int values[] = {8, 3, 5, 1, 9, 1, 4};
    const size_t count = sizeof values / sizeof values[0];
    int second_smallest;

    if (!find_second_smallest(values, count, &second_smallest)) {
        fputs("A distinct second smallest number does not exist.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%d\n", second_smallest) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}