#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int cube_sum_even(uint64_t n, uint64_t *result)
{
    uint64_t half;
    uint64_t other;
    uint64_t product;

    if (result == NULL) {
        return 0;
    }

    if ((n & UINT64_C(1)) == 0) {
        half = n / UINT64_C(2);
        other = n + UINT64_C(1);
    } else {
        half = (n + UINT64_C(1)) / UINT64_C(2);
        other = n;
    }

    if (half != 0 && other > UINT64_MAX / half) {
        return 0;
    }

    product = half * other;

    if (product != 0 && product > UINT64_MAX / product) {
        return 0;
    }

    product *= product;

    if (product > UINT64_MAX / UINT64_C(8)) {
        return 0;
    }

    *result = UINT64_C(8) * product;
    return 1;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[128];
    char *end;
    uintmax_t value;
    uint64_t sum;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (input[0] != '\0' && input[sizeof input - 2] != '\0' &&
        input[sizeof input - 2] != '\n') {
        int ch;

        do {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            ch = getchar();
        } while (ch != '\n' && ch != EOF);

        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    value = strtoumax(input, &end, 10);

    if (errno == ERANGE || end == input || value > UINT64_MAX) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!cube_sum_even((uint64_t)value, &sum)) {
        fputs("Input is too large\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", sum);
    return EXIT_SUCCESS;
}