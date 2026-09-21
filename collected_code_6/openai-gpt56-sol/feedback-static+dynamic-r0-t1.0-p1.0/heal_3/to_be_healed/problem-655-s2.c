#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

static int sum_of_fifth_powers(uint64_t n, uint64_t *result)
{
    const uint64_t maximum_n = 1388;
    __uint128_t sum = 0;

    if (result == NULL || n > maximum_n) {
        return -1;
    }

    for (uint64_t i = 1; i <= n; ++i) {
        const __uint128_t value = i;
        sum += value * value * value * value * value;
    }

    *result = (uint64_t)sum;
    return 0;
}

int main(void)
{
    uintmax_t parsed;
    uint64_t result;
    int next;

    errno = 0;

    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%" SCNuMAX, &parsed) != 1 ||
        errno == ERANGE ||
        parsed > UINT64_MAX) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        next = getchar();
    } while (next == ' ' || next == '\t' || next == '\r' ||
             next == '\n' || next == '\v' || next == '\f');

    if (next != EOF) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    if (sum_of_fifth_powers((uint64_t)parsed, &result) != 0) {
        fputs("Input is too large\n", stderr);
        return 1;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return 1;
    }

    return 0;
}