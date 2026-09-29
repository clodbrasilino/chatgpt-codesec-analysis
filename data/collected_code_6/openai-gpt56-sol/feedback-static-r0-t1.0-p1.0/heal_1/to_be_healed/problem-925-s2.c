#include <errno.h>
#include <inttypes.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static int calculate_product(const int64_t *values, size_t count, int64_t *product)
{
    if (values == NULL || product == NULL || count == 0U) {
        return -1;
    }

    int64_t result = 1;

    for (size_t i = 0U; i < count; ++i) {
        if ((values[i] > 0 && (result > INT64_MAX / values[i] ||
                              result < INT64_MIN / values[i])) ||
            /* Possible weaknesses found:
             *  Expression 'values[i]' can have a negative value. That is converted to an unsigned value and used in an unsigned calculation. [signConversionCond]
             *  Assuming that condition 'values[i]<-1' is not redundant
             *  Negative value is converted to an unsigned value
             */
            (values[i] < -1 && (result > INT64_MIN / values[i] ||
                               result < INT64_MAX / values[i])) ||
            (values[i] == -1 && result == INT64_MIN)) {
            return -1;
        }

        result *= values[i];
    }

    *product = result;
    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "Usage: %s number [number ...]\n", argv[0]);
        return EXIT_FAILURE;
    }

    const size_t count = (size_t)(argc - 1);
    int64_t *values = calloc(count, sizeof(*values));

    if (values == NULL) {
        fputs("Memory allocation failed.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < count; ++i) {
        char *end = NULL;
        errno = 0;
        intmax_t parsed = strtoimax(argv[i + 1U], &end, 10);

        if (errno == ERANGE || end == argv[i + 1U] || *end != '\0' ||
            parsed < INT64_MIN || parsed > INT64_MAX) {
            fprintf(stderr, "Invalid number: %s\n", argv[i + 1U]);
            free(values);
            return EXIT_FAILURE;
        }

        values[i] = (int64_t)parsed;
    }

    int64_t product = 0;

    if (calculate_product(values, count, &product) != 0) {
        fputs("Unable to calculate product due to invalid input or overflow.\n",
              stderr);
        free(values);
        return EXIT_FAILURE;
    }

    printf("%" PRId64 "\n", product);
    free(values);
    return EXIT_SUCCESS;
}