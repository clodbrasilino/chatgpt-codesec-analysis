#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int calculate_difference(uint64_t n, uint64_t *result)
{
    uint64_t a;
    uint64_t b;
    uint64_t sum;

    if (result == NULL || n == UINT64_MAX) {
        return 0;
    }

    a = n;
    b = n + UINT64_C(1);

    if ((a & UINT64_C(1)) == 0) {
        a /= UINT64_C(2);
    } else {
        b /= UINT64_C(2);
    }

    if (a != 0 && b > UINT64_MAX / a) {
        return 0;
    }

    sum = a * b;

    if (sum != 0 && sum > UINT64_MAX / sum) {
        return 0;
    }

    if (sum != 0 && (sum * sum) < sum) {
        return 0;
    }

    *result = (sum * sum) - sum;
    return 1;
}

int main(void)
{
    char input[128];
    char trailing;
    uint64_t n;
    uint64_t difference;

    fputs("Enter n: ", stdout);
    fflush(stdout);

    if (fgets(input, sizeof input, stdin) == NULL ||
        sscanf(input, " %" SCNu64 " %c", &n, &trailing) != 1) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!calculate_difference(n, &difference)) {
        fputs("Result is outside the supported range\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", difference);
    return EXIT_SUCCESS;
}