#include <stdio.h>
#include <stdlib.h>

size_t count_in_range(const int *list, size_t length, int lower, int upper)
{
    size_t count = 0;
    size_t i;

    if (list == NULL || lower > upper) {
        return 0;
    }

    for (i = 0; i < length; i++) {
        if (list[i] >= lower && list[i] <= upper) {
            count++;
        }
    }

    return count;
}

int main(void)
{
    int values[] = { 3, 7, 12, 5, 18, 9, 1, 14, 6, 20 };
    size_t length = sizeof(values) / sizeof(values[0]);
    int lower = 5;
    int upper = 15;
    size_t result;

    result = count_in_range(values, length, lower, upper);

    if (printf("Elements in range [%d, %d]: %zu\n", lower, upper, result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}