#include <stdio.h>
#include <stdlib.h>

static int last_element_parity_after_operations(const long long *array,
                                                 size_t length,
                                                 unsigned long long p)
{
    if (array == NULL || length == 0U) {
        return -1;
    }

    return (int)((array[length - 1U] & 1LL) ^ (p & 1ULL));
}

int main(void)
{
    size_t length;
    unsigned long long p;
    long long *array;
    int result;

    if (scanf("%zu %llu", &length, &p) != 2 || length == 0U ||
        length > SIZE_MAX / sizeof(*array)) {
        return EXIT_FAILURE;
    }

    array = malloc(length * sizeof(*array));
    if (array == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < length; ++i) {
        if (scanf("%lld", &array[i]) != 1) {
            free(array);
            return EXIT_FAILURE;
        }
    }

    result = last_element_parity_after_operations(array, length, p);
    free(array);

    if (result < 0) {
        return EXIT_FAILURE;
    }

    puts(result == 0 ? "Even" : "Odd");
    return EXIT_SUCCESS;
}