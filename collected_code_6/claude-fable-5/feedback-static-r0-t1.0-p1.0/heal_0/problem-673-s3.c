#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

bool list_to_integer(const int *list, size_t count, long *result)
{
    if (list == NULL || result == NULL || count == 0U) {
        return false;
    }

    long value = 0L;

    for (size_t i = 0U; i < count; i++) {
        if (list[i] < 0 || list[i] > 9) {
            return false;
        }

        if (value > (LONG_MAX - list[i]) / 10L) {
            return false;
        }

        value = (value * 10L) + (long)list[i];
    }

    *result = value;
    return true;
}

int main(void)
{
    int numbers[] = {1, 2, 3, 4, 5};
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    long combined = 0L;

    if (!list_to_integer(numbers, count, &combined)) {
        (void)fprintf(stderr, "Conversion failed\n");
        return EXIT_FAILURE;
    }

    if (printf("Combined integer: %ld\n", combined) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}