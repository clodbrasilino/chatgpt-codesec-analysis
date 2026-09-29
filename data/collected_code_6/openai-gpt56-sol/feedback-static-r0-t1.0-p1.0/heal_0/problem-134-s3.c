#include <stdio.h>
#include <stdlib.h>

static int check_last_after_operations(int *array, size_t length, size_t p)
{
    if (array == NULL || length == 0U) {
        return -1;
    }

    for (size_t operation = 0U; operation < p; ++operation) {
        array[length - 1U]++;
    }

    return array[length - 1U] % 2 == 0 ? 0 : 1;
}

int main(void)
{
    size_t length;
    size_t p;

    if (scanf("%zu %zu", &length, &p) != 2 || length == 0U ||
        length > SIZE_MAX / sizeof(int)) {
        return EXIT_FAILURE;
    }

    int *array = malloc(length * sizeof(*array));
    if (array == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < length; ++i) {
        if (scanf("%d", &array[i]) != 1) {
            free(array);
            return EXIT_FAILURE;
        }
    }

    int result = check_last_after_operations(array, length, p);
    if (result < 0) {
        free(array);
        return EXIT_FAILURE;
    }

    printf("%s\n", result == 0 ? "Even" : "Odd");
    free(array);

    return EXIT_SUCCESS;
}