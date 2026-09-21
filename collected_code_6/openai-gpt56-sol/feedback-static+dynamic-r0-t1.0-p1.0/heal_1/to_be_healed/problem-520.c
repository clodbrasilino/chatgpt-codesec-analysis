#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t gcd_uint64(uint64_t a, uint64_t b)
{
    while (b != 0U) {
        const uint64_t remainder = a % b;
        a = b;
        b = remainder;
    }

    return a;
}

static int lcm_array(const uint64_t values[], size_t count, uint64_t *result)
{
    uint64_t current = 1U;

    if (values == NULL || result == NULL || count == 0U) {
        return -1;
    }

    for (size_t i = 0U; i < count; ++i) {
        if (values[i] == 0U) {
            *result = 0U;
            return 0;
        }

        const uint64_t divisor = gcd_uint64(current, values[i]);
        const uint64_t quotient = current / divisor;

        if (quotient > UINT64_MAX / values[i]) {
            return -1;
        }

        current = quotient * values[i];
    }

    *result = current;
    return 0;
}

int main(void)
{
    size_t count = 0U;

    if (scanf("%zu", &count) != 1 || count == 0U ||
        count > SIZE_MAX / sizeof(uint64_t)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    uint64_t *values = malloc(count * sizeof(*values));
    if (values == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < count; ++i) {
        /* Possible weaknesses found:
         * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
         */
        if (scanf("%" SCNu64, &values[i]) != 1) {
            fputs("Invalid input\n", stderr);
            free(values);
            return EXIT_FAILURE;
        }
    }

    uint64_t result = 0U;
    if (lcm_array(values, count, &result) != 0) {
        fputs("LCM overflow\n", stderr);
        free(values);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    free(values);

    return EXIT_SUCCESS;
}