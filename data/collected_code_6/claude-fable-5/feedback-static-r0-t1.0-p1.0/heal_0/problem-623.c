#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int power_element(long long base, unsigned int exp, long long *result)
{
    long long acc = 1;

    while (exp > 0) {
        if (__builtin_mul_overflow(acc, base, &acc)) {
            return -1;
        }
        exp--;
    }

    *result = acc;
    return 0;
}

int power_list(const long long *input, long long *output, size_t count, unsigned int exp)
{
    size_t i;

    if (input == NULL || output == NULL) {
        return -1;
    }

    for (i = 0; i < count; i++) {
        if (power_element(input[i], exp, &output[i]) != 0) {
            return -1;
        }
    }

    return 0;
}

int main(void)
{
    long long values[] = {1, 2, 3, 4, 5};
    size_t count = sizeof(values) / sizeof(values[0]);
    unsigned int exp = 3;
    long long *results;
    size_t i;

    results = malloc(count * sizeof(*results));
    if (results == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (power_list(values, results, count, exp) != 0) {
        fprintf(stderr, "Computation failed due to overflow or invalid input\n");
        free(results);
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; i++) {
        if (printf("%lld^%u = %lld\n", values[i], exp, results[i]) < 0) {
            free(results);
            return EXIT_FAILURE;
        }
    }

    free(results);
    return EXIT_SUCCESS;
}