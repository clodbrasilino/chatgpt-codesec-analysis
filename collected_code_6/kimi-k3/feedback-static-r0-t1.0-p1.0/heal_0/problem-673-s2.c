#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>

int convert_list_to_integer(const int *numbers, size_t count, int *result)
{
    int value;
    size_t i;

    if (numbers == NULL || result == NULL) {
        return -1;
    }

    if (count == 0) {
        return -1;
    }

    value = 0;

    for (i = 0; i < count; i++) {
        if (numbers[i] < 0 || numbers[i] > 9) {
            return -1;
        }

        if (value > (INT_MAX - numbers[i]) / 10) {
            return -1;
        }

        value = value * 10 + numbers[i];
    }

    *result = value;
    return 0;
}

int main(void)
{
    int numbers[] = {1, 2, 3, 4, 5};
    size_t count;
    int result;
    int status;

    count = sizeof(numbers) / sizeof(numbers[0]);
    result = 0;

    status = convert_list_to_integer(numbers, count, &result);

    if (status != 0) {
        fprintf(stderr, "Conversion failed\n");
        return EXIT_FAILURE;
    }

    printf("Result: %d\n", result);

    return EXIT_SUCCESS;
}