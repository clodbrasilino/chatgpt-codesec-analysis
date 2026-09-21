#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>

static int largest_adjacent_product(const int64_t *values, size_t count, int64_t *result)
{
    if (values == NULL || result == NULL || count < 2) {
        return -1;
    }

    int64_t largest = values[0] * values[1];

    for (size_t i = 1; i < count - 1; ++i) {
        int64_t product = values[i] * values[i + 1];

        if (product > largest) {
            largest = product;
        }
    }

    *result = largest;
    return 0;
}

int main(void)
{
    size_t count;

    if (scanf("%zu", &count) != 1 || count < 2 || count > SIZE_MAX / sizeof(int32_t)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    int32_t *values = malloc(count * sizeof(*values));
    if (values == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        intmax_t input;

        errno = 0;
        /* Possible weaknesses found:
         * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
         */
        if (scanf("%" SCNdMAX, &input) != 1 || errno == ERANGE ||
            input < INT32_MIN || input > INT32_MAX) {
            fputs("Invalid input\n", stderr);
            free(values);
            return EXIT_FAILURE;
        }

        values[i] = (int32_t)input;
    }

    int64_t *wide_values = malloc(count * sizeof(*wide_values));
    if (wide_values == NULL) {
        perror("malloc");
        free(values);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        wide_values[i] = values[i];
    }

    int64_t result;
    if (largest_adjacent_product(wide_values, count, &result) != 0) {
        fputs("Unable to calculate product\n", stderr);
        free(wide_values);
        free(values);
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", result) < 0) {
        fputs("Output error\n", stderr);
        free(wide_values);
        free(values);
        return EXIT_FAILURE;
    }

    free(wide_values);
    free(values);
    return EXIT_SUCCESS;
}