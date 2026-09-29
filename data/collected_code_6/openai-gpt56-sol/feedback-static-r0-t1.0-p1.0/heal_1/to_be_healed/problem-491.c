#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'UINT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

static int geometric_sum(double first_term, double ratio, unsigned int terms,
                         double *result)
{
    double sum;
    double term;
    unsigned int i;

    if (result == NULL || !isfinite(first_term) || !isfinite(ratio)) {
        return 0;
    }

    sum = 0.0;
    term = first_term;

    for (i = 0U; i < terms; ++i) {
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

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    char *end;
    double first_term;
    double ratio;
    double sum;
    unsigned long parsed_terms;
    unsigned int terms;

    if (argc != 4) {
        fprintf(stderr, "Usage: %s <first_term> <ratio> <terms>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    first_term = strtod(argv[1], &end);
    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        !isfinite(first_term)) {
        fprintf(stderr, "Invalid first term\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    ratio = strtod(argv[2], &end);
    if (errno == ERANGE || end == argv[2] || *end != '\0' ||
        !isfinite(ratio)) {
        fprintf(stderr, "Invalid ratio\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    parsed_terms = strtoul(argv[3], &end, 10);
    if (errno == ERANGE || end == argv[3] || *end != '\0' ||
        /* Possible weaknesses found:
         *  each undeclared identifier is reported only once for each function it appears in
         *  use of undeclared identifier 'UINT_MAX'
         *  'UINT_MAX' undeclared (first use in this function)
         */
        parsed_terms > UINT_MAX) {
        fprintf(stderr, "Invalid number of terms\n");
        return EXIT_FAILURE;
    }
    terms = (unsigned int)parsed_terms;

    if (!geometric_sum(first_term, ratio, terms, &sum)) {
        fprintf(stderr, "The series sum is not representable\n");
        return EXIT_FAILURE;
    }

    printf("%.17g\n", sum);
    return EXIT_SUCCESS;
}