#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int cube_sum(uint64_t n, uint64_t *result)
{
    uint64_t a;
    uint64_t b;
    uint64_t product;

    if (result == NULL || n > UINT64_C(92681)) {
        return 0;
    }

    if ((n & UINT64_C(1)) == 0) {
        a = n / UINT64_C(2);
        b = n + UINT64_C(1);
    } else {
        a = n;
        b = (n + UINT64_C(1)) / UINT64_C(2);
    }

    product = a * b;
    *result = product * product;
    return 1;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[128];
    char *end;
    uintmax_t value;
    uint64_t result;

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    value = strtoumax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || value > UINT64_MAX) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!cube_sum((uint64_t)value, &result)) {
        fputs("Input is out of range\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}