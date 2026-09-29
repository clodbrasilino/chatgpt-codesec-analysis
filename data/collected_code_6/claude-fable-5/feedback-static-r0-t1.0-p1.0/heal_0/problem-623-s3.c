#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int power_elements(const long long *input, long long *output, size_t count, unsigned int n)
{
    size_t i;
    unsigned int j;

    if (input == NULL || output == NULL) {
        return -1;
    }

    for (i = 0; i < count; i++) {
        long long result = 1;
        for (j = 0; j < n; j++) {
            if (input[i] != 0) {
                if (result > LLONG_MAX / llabs(input[i]) ||
                    result < LLONG_MIN / llabs(input[i])) {
                    return -1;
                }
            }
            result *= input[i];
        }
        output[i] = result;
    }

    return 0;
}

int main(void)
{
    long long numbers[] = {1, 2, 3, 4, 5};
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    unsigned int n = 3;
    size_t i;

    long long *results = malloc(count * sizeof(*results));
    if (results == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (power_elements(numbers, results, count, n) != 0) {
        fprintf(stderr, "Computation failed\n");
        free(results);
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; i++) {
        if (printf("%lld^%u = %lld\n", numbers[i], n, results[i]) < 0) {
            free(results);
            return EXIT_FAILURE;
        }
    }

    free(results);
    return EXIT_SUCCESS;
}