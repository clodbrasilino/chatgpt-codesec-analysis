#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int cube_sum(uint64_t n, uint64_t *result)
{
    uint64_t a;
    uint64_t b;

    if (result == NULL || n > 92681U) {
        return 0;
    }

    if ((n & 1U) == 0U) {
        a = n / 2U;
        b = n + 1U;
    } else {
        a = n;
        b = (n + 1U) / 2U;
    }

    *result = (a * b) * (a * b);
    return 1;
}

int main(void)
{
    uint64_t n;
    uint64_t result;
    int input_status;

    input_status = scanf("%" SCNu64, &n);
    if (input_status != 1) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!cube_sum(n, &result)) {
        fputs("Input is out of range\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}