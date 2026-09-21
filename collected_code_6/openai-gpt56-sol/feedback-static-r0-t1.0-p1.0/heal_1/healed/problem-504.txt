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
    char input[128];
    char trailing;
    char *end;
    uintmax_t parsed;
    uint64_t n;
    uint64_t result;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    parsed = strtoumax(input, &end, 10);
    if (end == input || parsed > UINT64_MAX) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' || *end == '\n' ||
           *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0' || sscanf(input, " %" SCNu64 " %c", &n, &trailing) != 1) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    n = (uint64_t)parsed;

    if (!cube_sum(n, &result)) {
        fputs("Input is out of range\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}