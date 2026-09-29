#include <stdio.h>
#include <stdlib.h>

static int count_self_inverse(const long long *array, size_t length, long long p, size_t *count)
{
    size_t total = 0;

    if (array == NULL || count == NULL || p <= 1) {
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
        long long residue = array[i] % p;

        if (residue < 0) {
            residue += p;
        }

        if (residue == 1 || residue == p - 1) {
            ++total;
        }
    }

    *count = total;
    return 1;
}

int main(void)
{
    size_t length;
    long long p;
    long long *array = NULL;
    size_t count;

    if (scanf("%zu %lld", &length, &p) != 2 || p <= 1) {
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX / sizeof(*array)) {
        return EXIT_FAILURE;
    }

    if (length > 0) {
        array = malloc(length * sizeof(*array));
        if (array == NULL) {
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < length; ++i) {
        if (scanf("%lld", &array[i]) != 1) {
            free(array);
            return EXIT_FAILURE;
        }
    }

    if (!count_self_inverse(array, length, p, &count)) {
        free(array);
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", count) < 0) {
        free(array);
        return EXIT_FAILURE;
    }

    free(array);
    return EXIT_SUCCESS;
}