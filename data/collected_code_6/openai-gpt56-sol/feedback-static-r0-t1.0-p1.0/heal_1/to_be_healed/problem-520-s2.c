#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t gcd_uint64(uint64_t a, uint64_t b)
{
    while (b != 0U) {
        uint64_t remainder = a % b;
        a = b;
        b = remainder;
    }

    return a;
}

static int lcm_array(const uint64_t values[], size_t count, uint64_t *result)
{
    uint64_t current;

    if (values == NULL || result == NULL || count == 0U) {
        return 0;
    }

    current = values[0];

    for (size_t i = 1U; i < count; ++i) {
        uint64_t divisor;

        if (current == 0U || values[i] == 0U) {
            current = 0U;
            continue;
        }

        divisor = gcd_uint64(current, values[i]);

        if ((current / divisor) > (UINT64_MAX / values[i])) {
            return 0;
        }

        current = (current / divisor) * values[i];
    }

    *result = current;
    return 1;
}

int main(void)
{
    size_t count;
    uint64_t *values;
    uint64_t result;

    if (scanf("%zu", &count) != 1 || count == 0U ||
        count > (SIZE_MAX / sizeof(*values))) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    values = malloc(count * sizeof(*values));
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

    if (!lcm_array(values, count, &result)) {
        fputs("LCM overflow\n", stderr);
        free(values);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    free(values);
    return EXIT_SUCCESS;
}