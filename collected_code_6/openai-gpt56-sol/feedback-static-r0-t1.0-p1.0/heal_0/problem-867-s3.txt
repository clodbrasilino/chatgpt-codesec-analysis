#include <stdio.h>
#include <stdlib.h>

static int minimum_addition_for_even_sum(const int *array, size_t length)
{
    int parity = 0;

    for (size_t i = 0; i < length; ++i) {
        parity ^= (array[i] & 1);
    }

    return parity;
}

int main(void)
{
    size_t length;

    if (scanf("%zu", &length) != 1 || length == 0 ||
        length > SIZE_MAX / sizeof(int)) {
        return EXIT_FAILURE;
    }

    int *array = malloc(length * sizeof(*array));
    if (array == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        if (scanf("%d", &array[i]) != 1) {
            free(array);
            return EXIT_FAILURE;
        }
    }

    printf("%d\n", minimum_addition_for_even_sum(array, length));

    free(array);
    return EXIT_SUCCESS;
}