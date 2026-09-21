#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

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
    int64_t *products;
    int64_t best;
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

static int read_size(size_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[128];
    char *end;
    uintmax_t parsed;

    if (value == NULL || fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 0;
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || parsed == 0 ||
        parsed > SIZE_MAX || (*end != '\n' && *end != '\0')) {
        return 0;
    }

    *value = (size_t)parsed;
    return 1;
}

static int read_int64(int64_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[128];
    char *end;
    intmax_t parsed;

    if (value == NULL || fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 0;
    }

    errno = 0;
    end = NULL;
    parsed = strtoimax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || parsed < INT64_MIN ||
        parsed > INT64_MAX || (*end != '\n' && *end != '\0')) {
        return 0;
    }

    *value = (int64_t)parsed;
    return 1;
}

int main(void)
{
    size_t length;
    int64_t *values;
    int64_t maximum;
    size_t i;

    if (!read_size(&length) ||
        length > SIZE_MAX / sizeof(*values)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    values = malloc(length * sizeof(*values));
    if (values == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }

    for (i = 0; i < length; ++i) {
        if (!read_int64(&values[i])) {
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

    if (printf("%" PRId64 "\n", maximum) < 0) {
        free(values);
        return EXIT_FAILURE;
    }

    free(values);
    return EXIT_SUCCESS;
}