#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

long convert_list_to_integer(const int *list, size_t size)
{
    long result = 0;
    size_t i;

    if (list == NULL || size == 0) {
        return 0;
    }

    for (i = 0; i < size; i++) {
        if (list[i] < 0 || list[i] > 9) {
            return -1;
        }

        if (result > (LONG_MAX - list[i]) / 10) {
            return -1;
        }

        result = result * 10 + list[i];
    }

    return result;
}

int main(void)
{
    int numbers[] = {1, 2, 3, 4, 5};
    size_t size = sizeof(numbers) / sizeof(numbers[0]);
    long result;

    result = convert_list_to_integer(numbers, size);

    if (result == -1) {
        fprintf(stderr, "Error: Invalid input or overflow occurred\n");
        return EXIT_FAILURE;
    }

    printf("Result: %ld\n", result);

    return EXIT_SUCCESS;
}