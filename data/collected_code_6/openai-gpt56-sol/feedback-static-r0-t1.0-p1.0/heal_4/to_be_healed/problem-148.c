#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t digit_sum(uint64_t value)
{
    uint64_t sum = 0;

    do {
        sum += value % UINT64_C(10);
        value /= UINT64_C(10);
    } while (value != 0);

    return sum;
}

static void divide_max_digit_sum(uint64_t number,
                                 uint64_t *first,
                                 uint64_t *second)
{
    uint64_t power = UINT64_C(1);

    while (power <= number / UINT64_C(10)) {
        power *= UINT64_C(10);
    }

    *first = power - UINT64_C(1);
    *second = number - *first;
}

int main(void)
{
    uintmax_t parsed;
    uint64_t number;
    uint64_t first;
    uint64_t second;
    int ch;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != EOF && isspace((unsigned char)ch)) {
    }

    if (ch == EOF) {
        return EXIT_FAILURE;
    }

    if (ungetc(ch, stdin) == EOF) {
        return EXIT_FAILURE;
    }

    errno = 0;
    /* Possible weaknesses found:
     * Flawfinder fscanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (fscanf(stdin, "%" SCNuMAX, &parsed) != 1 ||
        errno == ERANGE ||
        parsed == 0 ||
        parsed > UINT64_MAX) {
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != EOF) {
        if (!isspace((unsigned char)ch)) {
            return EXIT_FAILURE;
        }
    }

    if (ferror(stdin)) {
        return EXIT_FAILURE;
    }

    number = (uint64_t)parsed;
    divide_max_digit_sum(number, &first, &second);

    if (printf("%" PRIu64 " %" PRIu64 "\n", first, second) < 0) {
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n",
               digit_sum(first) + digit_sum(second)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}