#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

int count_in_range(const int *list, size_t size, int min_val, int max_val, size_t *count) {
    if (list == NULL || count == NULL) {
        return -1;
    }

    if (min_val > max_val) {
        return -1;
    }

    *count = 0;

    for (size_t i = 0; i < size; i++) {
        if (list[i] >= min_val && list[i] <= max_val) {
            (*count)++;
        }
    }

    return 0;
}

int main(void) {
    const int numbers[] = {3, 7, 12, 5, 9, 21, 15, 8, 10};
    size_t size = sizeof(numbers) / sizeof(numbers[0]);
    int min_val = 7;
    int max_val = 15;
    size_t count = 0;

    int status = count_in_range(numbers, size, min_val, max_val, &count);

    if (status != 0) {
        fprintf(stderr, "Invalid arguments provided to count_in_range.\n");
        return EXIT_FAILURE;
    }

    printf("%zu\n", count);

    return EXIT_SUCCESS;
}