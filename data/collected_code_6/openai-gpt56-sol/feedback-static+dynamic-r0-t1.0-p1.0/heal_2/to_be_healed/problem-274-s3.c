#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_even_index_binomial(unsigned int n, uint64_t *result)
{
    if (result == NULL) {
        return 0;
    }

    if (n == 0U) {
        *result = UINT64_C(1);
        return 1;
    }

    if (n > 64U) {
        return 0;
    }

    *result = UINT64_C(1) << (n - 1U);
    return 1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    char *end = NULL;
    unsigned long value;
    uint64_t sum;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <nonnegative integer up to 64>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoul(argv[1], &end, 10);

    if (errno != 0 || end == argv[1] || *end != '\0' || value > 64UL) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (!sum_even_index_binomial((unsigned int)value, &sum)) {
        fprintf(stderr, "Unable to compute result\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", sum);
    return EXIT_SUCCESS;
}