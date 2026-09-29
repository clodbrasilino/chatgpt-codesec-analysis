#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

int convert_list_to_integer(const int *list, size_t size, int *result) {
    if (list == NULL || result == NULL || size == 0) {
        return -1;
    }

    int value = 0;
    for (size_t i = 0; i < size; i++) {
        if (list[i] < 0 || list[i] > 9) {
            return -1;
        }

        if (value > (INT_MAX - list[i]) / 10) {
            return -1;
        }

        value = value * 10 + list[i];
    }

    *result = value;
    return 0;
}

int main(void) {
    int numbers[] = {1, 2, 3, 4, 5};
    size_t size = sizeof(numbers) / sizeof(numbers[0]);
    int result = 0;

    if (convert_list_to_integer(numbers, size, &result) != 0) {
        fprintf(stderr, "Conversion failed\n");
        return EXIT_FAILURE;
    }

    printf("%d\n", result);
    return EXIT_SUCCESS;
}