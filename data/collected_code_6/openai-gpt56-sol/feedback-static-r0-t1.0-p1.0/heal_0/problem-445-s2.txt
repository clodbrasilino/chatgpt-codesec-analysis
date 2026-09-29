#include <stdio.h>
#include <stdlib.h>

static int multiply_tuples(const long long *tuple1, const long long *tuple2,
                           long long *result, size_t length)
{
    if (tuple1 == NULL || tuple2 == NULL || result == NULL) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        result[i] = tuple1[i] * tuple2[i];
    }

    return 0;
}

int main(void)
{
    const long long tuple1[] = {1, 2, 3, 4};
    const long long tuple2[] = {5, 6, 7, 8};
    const size_t length = sizeof(tuple1) / sizeof(tuple1[0]);

    if (length != sizeof(tuple2) / sizeof(tuple2[0])) {
        return EXIT_FAILURE;
    }

    long long *result = malloc(length * sizeof(*result));
    if (result == NULL) {
        return EXIT_FAILURE;
    }

    if (multiply_tuples(tuple1, tuple2, result, length) != 0) {
        free(result);
        return EXIT_FAILURE;
    }

    if (printf("(") < 0) {
        free(result);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        if (printf("%lld%s", result[i], i + 1 < length ? ", " : ")\n") < 0) {
            free(result);
            return EXIT_FAILURE;
        }
    }

    free(result);
    return EXIT_SUCCESS;
}