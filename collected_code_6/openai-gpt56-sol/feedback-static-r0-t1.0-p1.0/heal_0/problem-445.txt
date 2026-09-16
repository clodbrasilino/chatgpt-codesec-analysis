#include <stdio.h>
#include <stdlib.h>

static int multiply_tuples(const long long *first, const long long *second,
                           long long *result, size_t length)
{
    if ((length > 0U) &&
        (first == NULL || second == NULL || result == NULL)) {
        return -1;
    }

    for (size_t index = 0U; index < length; ++index) {
        result[index] = first[index] * second[index];
    }

    return 0;
}

int main(void)
{
    size_t length = 0U;

    if (scanf("%zu", &length) != 1) {
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX / sizeof(long long)) {
        return EXIT_FAILURE;
    }

    long long *first = malloc(length * sizeof(*first));
    long long *second = malloc(length * sizeof(*second));
    long long *result = malloc(length * sizeof(*result));

    if (length > 0U && (first == NULL || second == NULL || result == NULL)) {
        free(first);
        free(second);
        free(result);
        return EXIT_FAILURE;
    }

    for (size_t index = 0U; index < length; ++index) {
        if (scanf("%lld", &first[index]) != 1) {
            free(first);
            free(second);
            free(result);
            return EXIT_FAILURE;
        }
    }

    for (size_t index = 0U; index < length; ++index) {
        if (scanf("%lld", &second[index]) != 1) {
            free(first);
            free(second);
            free(result);
            return EXIT_FAILURE;
        }
    }

    if (multiply_tuples(first, second, result, length) != 0) {
        free(first);
        free(second);
        free(result);
        return EXIT_FAILURE;
    }

    putchar('(');
    for (size_t index = 0U; index < length; ++index) {
        if (index > 0U) {
            fputs(", ", stdout);
        }
        printf("%lld", result[index]);
    }
    puts(")");

    free(first);
    free(second);
    free(result);

    return EXIT_SUCCESS;
}