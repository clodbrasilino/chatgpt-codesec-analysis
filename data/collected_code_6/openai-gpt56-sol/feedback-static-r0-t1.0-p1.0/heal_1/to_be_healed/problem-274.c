#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'UINT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

static int sum_even_index_binomial(unsigned int n, uintmax_t *result)
{
    if (result == NULL) {
        return 0;
    }

    if (n == 0U) {
        *result = 1U;
        return 1;
    }

    if (n > (unsigned int)(sizeof(uintmax_t) * 8U)) {
        return 0;
    }

    *result = UINTMAX_C(1) << (n - 1U);
    return 1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    char *end = NULL;
    uintmax_t input;
    uintmax_t result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <nonnegative integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    input = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        /* Possible weaknesses found:
         *  each undeclared identifier is reported only once for each function it appears in
         *  use of undeclared identifier 'UINT_MAX'
         *  'UINT_MAX' undeclared (first use in this function)
         */
        input > (uintmax_t)UINT_MAX) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (!sum_even_index_binomial((unsigned int)input, &result)) {
        fprintf(stderr, "Result cannot be represented\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIuMAX "\n", result);
    return EXIT_SUCCESS;
}