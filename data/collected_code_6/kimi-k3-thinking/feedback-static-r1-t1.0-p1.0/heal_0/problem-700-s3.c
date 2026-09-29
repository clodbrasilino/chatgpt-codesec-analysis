#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>

size_t count_in_range(const int *list, size_t size, int lower, int upper)
{
    size_t count = 0;
    size_t i;

    if (list == NULL) {
        return 0;
    }

    for (i = 0; i < size; i++) {
        if (list[i] >= lower && list[i] <= upper) {
            count++;
        }
    }

    return count;
}

int main(void)
{
    size_t size = 10;
    int *list;
    size_t i;
    size_t result;
    int lower = 5;
    int upper = 20;

    if (size > SIZE_MAX / sizeof(int)) {
        fprintf(stderr, "Invalid size requested\n");
        return EXIT_FAILURE;
    }

    list = malloc(size * sizeof(*list));

    if (list == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < size; i++) {
        list[i] = (int)(i * 3 + 1);
    }

    result = count_in_range(list, size, lower, upper);

    printf("Number of elements within [%d, %d]: %zu\n", lower, upper, result);

    free(list);
    list = NULL;

    return EXIT_SUCCESS;
}