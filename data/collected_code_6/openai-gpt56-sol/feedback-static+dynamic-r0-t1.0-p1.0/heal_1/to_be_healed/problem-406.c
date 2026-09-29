#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static unsigned int parity(unsigned long long number)
{
    unsigned int result = 0U;

    while (number != 0ULL) {
        result ^= 1U;
        number &= number - 1ULL;
    }

    return result;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[128];
    char *end = NULL;
    unsigned long long number;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    number = strtoull(input, &end, 0);

    if (end == input || errno == ERANGE) {
        fputs("Invalid number.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid trailing characters.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%u\n", parity(number));
    return EXIT_SUCCESS;
}