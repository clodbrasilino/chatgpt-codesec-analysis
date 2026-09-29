#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>

static int next_power_of_two(uint64_t n, uint64_t *result)
{
    if (result == NULL || n == 0 || n > (UINT64_C(1) << 63)) {
        return 0;
    }

    n--;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    n |= n >> 32;

    *result = n + 1;
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
    uint64_t n;
    uint64_t result;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = input;
    while (isspace((unsigned char)*end)) {
        end++;
    }

    if (*end == '-' || *end == '\0') {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    value = strtoumax(end, &end, 10);

    if (errno == ERANGE || value > UINT64_MAX) {
        fputs("Input is out of range\n", stderr);
        return EXIT_FAILURE;
    }

    if (end == input) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        end++;
    }

    if (*end != '\0') {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    n = (uint64_t)value;

    if (!next_power_of_two(n, &result)) {
        fputs("Input is out of range\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}