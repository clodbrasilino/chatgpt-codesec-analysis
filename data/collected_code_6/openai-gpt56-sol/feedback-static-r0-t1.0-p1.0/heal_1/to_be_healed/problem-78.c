#include <stdio.h>
#include <stdlib.h>
/* Possible weaknesses found:
 *  'SCNu64' is defined in header '<inttypes.h>'; this is probably fixable by adding '#include <inttypes.h>'
 */
#include <stdint.h>

static int has_odd_set_bits(uint64_t value)
{
    int parity = 0;

    while (value != 0U) {
        parity ^= 1;
        value &= value - UINT64_C(1);
    }

    return parity;
}

static size_t count_odd_set_bits(const uint64_t *values, size_t count)
{
    size_t result = 0U;

    for (size_t i = 0U; i < count; ++i) {
        if (has_odd_set_bits(values[i]) != 0) {
            ++result;
        }
    }

    return result;
}

int main(void)
{
    size_t count;

    if (scanf("%zu", &count) != 1) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(uint64_t)) {
        fputs("Input size is too large\n", stderr);
        return EXIT_FAILURE;
    }

    uint64_t *values = NULL;

    if (count != 0U) {
        values = malloc(count * sizeof(*values));
        if (values == NULL) {
            fputs("Memory allocation failed\n", stderr);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0U; i < count; ++i) {
        /* Possible weaknesses found:
         *  to match this '('
         *  expected ')' before 'SCNu64'
         * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
         *  expected ')'
         */
        if (scanf("%" SCNu64, &values[i]) != 1) {
            fputs("Invalid input\n", stderr);
            free(values);
            return EXIT_FAILURE;
        }
    }

    printf("%zu\n", count_odd_set_bits(values, count));
    free(values);

    return EXIT_SUCCESS;
}