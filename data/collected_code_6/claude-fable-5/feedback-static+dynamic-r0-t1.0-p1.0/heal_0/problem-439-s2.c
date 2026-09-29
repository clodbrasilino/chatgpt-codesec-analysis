#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int convert_list_to_integer(const int *list, size_t count, long *result)
{
    size_t i;
    long value = 0;

    if (list == NULL || result == NULL || count == 0) {
        return -1;
    }

    for (i = 0; i < count; i++) {
        if (list[i] < 0 || list[i] > 9) {
            return -1;
        }
        if (value > (LONG_MAX - list[i]) / 10) {
            return -1;
        }
        value = value * 10 + list[i];
    }

    *result = value;
    return 0;
}

int main(void)
{
    int numbers[] = {1, 2, 3, 4, 5};
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    long result = 0;

    if (convert_list_to_integer(numbers, count, &result) != 0) {
        fprintf(stderr, "Conversion failed\n");
        return EXIT_FAILURE;
    }

    if (printf("Converted integer: %ld\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}