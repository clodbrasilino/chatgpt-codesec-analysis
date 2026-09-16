#include <errno.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int geometric_sum(double first_term, double ratio, size_t terms,
                         double *result)
{
    if (result == NULL || !isfinite(first_term) || !isfinite(ratio)) {
        return 0;
    }

    double sum = 0.0;
    double term = first_term;

    for (size_t i = 0; i < terms; ++i) {
        sum += term;
        if (!isfinite(sum)) {
            return 0;
        }

        if (i + 1U < terms) {
            term *= ratio;
            if (!isfinite(term)) {
                return 0;
            }
        }
    }

    *result = sum;
    return 1;
}

static int parse_double(const char *text, double *value)
{
    if (text == NULL || value == NULL || *text == '\0') {
        return 0;
    }

    char *end = NULL;
    errno = 0;
    const double parsed = strtod(text, &end);

    if (errno == ERANGE || end == text || *end != '\0' || !isfinite(parsed)) {
        return 0;
    }

    *value = parsed;
    return 1;
}

static int parse_size(const char *text, size_t *value)
{
    if (text == NULL || value == NULL || *text == '\0' || *text == '-') {
        return 0;
    }

    char *end = NULL;
    errno = 0;
    const unsigned long long parsed = strtoull(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed > (unsigned long long)SIZE_MAX) {
        return 0;
    }

    *value = (size_t)parsed;
    return 1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <first_term> <ratio> <term_count>\n",
                argv[0]);
        return EXIT_FAILURE;
    }

    double first_term = 0.0;
    double ratio = 0.0;
    size_t terms = 0U;
    double sum = 0.0;

    if (!parse_double(argv[1], &first_term) ||
        !parse_double(argv[2], &ratio) ||
        !parse_size(argv[3], &terms)) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!geometric_sum(first_term, ratio, terms, &sum)) {
        fputs("The sum cannot be represented as a finite double.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%.17g\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}