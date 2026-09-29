#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>

bool find_second_smallest(const int values[], size_t count, int *result)
{
    if (values == NULL || result == NULL || count < 2U) {
        return false;
    }

    int smallest = values[0];
    int second_smallest = 0;
    bool found_second = false;

    for (size_t i = 1U; i < count; ++i) {
        if (values[i] < smallest) {
            second_smallest = smallest;
            smallest = values[i];
            found_second = true;
        } else if (values[i] > smallest &&
                   (!found_second || values[i] < second_smallest)) {
            second_smallest = values[i];
            found_second = true;
        }
    }

    if (!found_second) {
        return false;
    }

    *result = second_smallest;
    return true;
}

int main(void)
{
    const int values[] = {7, 3, 9, 1, 4, 1};
    const size_t count = sizeof values / sizeof values[0];
    int second_smallest = 0;

    if (!find_second_smallest(values, count, &second_smallest)) {
        fputs("No distinct second smallest number exists.\n", stderr);
        return 1;
    }

    if (printf("%d\n", second_smallest) < 0) {
        return 1;
    }

    return 0;
}