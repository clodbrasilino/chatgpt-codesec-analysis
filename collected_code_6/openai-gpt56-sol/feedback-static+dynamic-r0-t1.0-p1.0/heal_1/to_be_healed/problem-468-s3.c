#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'SCNd64' is defined in header '<inttypes.h>'; this is probably fixable by adding '#include <inttypes.h>'
  */

static int multiply_checked(int64_t a, int64_t b, int64_t *result)
{
    if (result == NULL) {
        return 0;
    }

    if ((a > 0 && b > 0 && a > INT64_MAX / b) ||
        (a > 0 && b < 0 && b < INT64_MIN / a) ||
        (a < 0 && b > 0 && a < INT64_MIN / b) ||
        (a < 0 && b < 0 && a < INT64_MAX / b)) {
        return 0;
    }

    *result = a * b;
    return 1;
}

static int maximum_increasing_subsequence_product(
    const int64_t *values,
    size_t length,
    int64_t *maximum)
{
    int64_t *products = NULL;
    int64_t best = 0;
    size_t i;

    if (values == NULL || maximum == NULL || length == 0 ||
        length > SIZE_MAX / sizeof(*products)) {
        return 0;
    }

    products = malloc(length * sizeof(*products));
    if (products == NULL) {
        return 0;
    }

    best = values[0];

    for (i = 0; i < length; ++i) {
        size_t j;

        products[i] = values[i];

        for (j = 0; j < i; ++j) {
            int64_t candidate;

            if (values[j] < values[i] &&
                multiply_checked(products[j], values[i], &candidate) &&
                candidate > products[i]) {
                products[i] = candidate;
            }
        }

        if (products[i] > best) {
            best = products[i];
        }
    }

    free(products);
    *maximum = best;
    return 1;
}

int main(void)
{
    size_t length;
    int64_t *values = NULL;
    int64_t maximum;
    size_t i;

    if (scanf("%zu", &length) != 1 || length == 0 ||
        length > SIZE_MAX / sizeof(*values)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    values = malloc(length * sizeof(*values));
    if (values == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }

    for (i = 0; i < length; ++i) {
        /* Possible weaknesses found:
         *  expected ')' before 'SCNd64'
         *  to match this '('
         * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
         *  expected ')'
         */
        if (scanf("%" SCNd64, &values[i]) != 1) {
            fputs("Invalid input\n", stderr);
            free(values);
            return EXIT_FAILURE;
        }
    }

    if (!maximum_increasing_subsequence_product(values, length, &maximum)) {
        fputs("Unable to calculate result\n", stderr);
        free(values);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     *  expected ')'
     *  to match this '('
     *  expected ')' before 'PRId64'
     *  'PRId64' is defined in header '<inttypes.h>'; this is probably fixable by adding '#include <inttypes.h>'
     */
    if (printf("%" PRId64 "\n", maximum) < 0) {
        free(values);
        return EXIT_FAILURE;
    }

    free(values);
    return EXIT_SUCCESS;
}