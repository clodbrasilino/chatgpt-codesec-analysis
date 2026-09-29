#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_fourth_powers_even(uint64_t n, uint64_t *result)
{
    uint64_t sum = 0;

    if (result == NULL || n > UINT64_C(7131)) {
        return 0;
    }

    for (uint64_t i = 1; i <= n; ++i) {
        uint64_t even = UINT64_C(2) * i;
        uint64_t square = even * even;
        uint64_t fourth_power = square * square;

        if (sum > UINT64_MAX - fourth_power) {
            return 0;
        }

        sum += fourth_power;
    }

    *result = sum;
    return 1;
}

static int read_uint64(uint64_t *value)
{
    uintmax_t parsed;
    char *end;

    if (value == NULL) {
        return 0;
    }

    errno = 0;
    /* Possible weaknesses found:
     *  Value stored to 'parsed' is never read [deadcode.DeadStores]
     *  parsed is assigned
     */
    parsed = strtoumax("", &end, 10);

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    int ch = getchar();

    while (ch != EOF && isspace((unsigned char)ch)) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
    }

    if (ch == EOF || ch == '-' || ch == '+') {
        return 0;
    }

    if (!isdigit((unsigned char)ch)) {
        return 0;
    }

    /* Possible weaknesses found:
     *  Variable 'parsed' is reassigned a value before the old one has been used. [redundantAssignment]
     *  parsed is overwritten
     */
    parsed = 0;

    do {
        unsigned int digit = (unsigned int)(ch - '0');

        if (parsed > (UINT64_MAX - digit) / UINTMAX_C(10)) {
            do {
                /* Possible weaknesses found:
                 * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                ch = getchar();
            } while (ch != '\n' && ch != EOF);
            return 0;
        }

        parsed = parsed * UINTMAX_C(10) + digit;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
    } while (ch != EOF && isdigit((unsigned char)ch));

    while (ch != EOF && ch != '\n') {
        if (!isspace((unsigned char)ch)) {
            do {
                /* Possible weaknesses found:
                 * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                ch = getchar();
            } while (ch != '\n' && ch != EOF);
            return 0;
        }

        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
    }

    *value = (uint64_t)parsed;
    return 1;
}

int main(void)
{
    uint64_t value;
    uint64_t result;

    if (!read_uint64(&value)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!sum_fourth_powers_even(value, &result)) {
        fputs("Result exceeds the supported range\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}