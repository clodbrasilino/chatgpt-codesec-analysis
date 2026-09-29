#include <errno.h>
#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_perfect_square(uint64_t number)
{
    uint64_t root = (uint64_t)sqrtl((long double)number);

    while (root > 0U && root > number / root) {
        --root;
    }

    while (root < UINT64_MAX && root + 1U <= number / (root + 1U)) {
        ++root;
    }

    return root == 0U ? number == 0U : root == number / root && number % root == 0U;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[128];
    char *end = NULL;
    uintmax_t value;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoumax(input, &end, 10);

    if (end == input || errno == ERANGE || value > UINT64_MAX) {
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        return EXIT_FAILURE;
    }

    if (printf("%s\n", is_perfect_square((uint64_t)value) ? "true" : "false") < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}