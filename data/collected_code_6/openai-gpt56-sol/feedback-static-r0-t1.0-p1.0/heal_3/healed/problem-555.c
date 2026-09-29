#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int calculate_difference(uint64_t n, uint64_t *result)
{
    if (result == NULL || n == UINT64_MAX) {
        return 0;
    }

    uint64_t a = n;
    uint64_t b = n + UINT64_C(1);

    if ((a & UINT64_C(1)) == 0) {
        a /= UINT64_C(2);
    } else {
        b /= UINT64_C(2);
    }

    if (a != 0 && b > UINT64_MAX / a) {
        return 0;
    }

    const uint64_t sum = a * b;

    if (sum != 0 && sum > UINT64_MAX / sum) {
        return 0;
    }

    const uint64_t square = sum * sum;

    if (square < sum) {
        return 0;
    }

    *result = square - sum;
    return 1;
}

int main(void)
{
    char input[128];
    char extra;
    uint64_t n;
    uint64_t difference;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (sscanf(input, " %" SCNu64 " %c", &n, &extra) != 1) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (calculate_difference(n, &difference) == 0) {
        fputs("Result is out of range\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", difference) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}