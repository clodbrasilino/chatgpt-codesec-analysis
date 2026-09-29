#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t max_exchange_sum(uint64_t n)
{
    if (n < UINT64_C(12)) {
        return n;
    }

    uint64_t a = max_exchange_sum(n / UINT64_C(2));
    uint64_t b = max_exchange_sum(n / UINT64_C(3));
    uint64_t c = max_exchange_sum(n / UINT64_C(4));

    if (a > UINT64_MAX - b) {
        return UINT64_MAX;
    }

    uint64_t sum = a + b;

    if (sum > UINT64_MAX - c) {
        return UINT64_MAX;
    }

    sum += c;
    return sum > n ? sum : n;
}

static int read_uint64(uint64_t *result)
{
    errno = 0;
    char *end = NULL;
    /* Possible weaknesses found:
     *  value is initialized
     *  Value stored to 'value' during its initialization is never read [deadcode.DeadStores]
     */
    uintmax_t value = strtoumax("", &end, 10);
    int ch;
    int saw_digit = 0;
    int overflow = 0;
    int trailing = 0;

    /* Possible weaknesses found:
     *  value is overwritten
     *  Redundant initialization for 'value'. The initialized value is overwritten before it is read. [redundantInitialization]
     */
    value = 0;

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    } while (ch == ' ' || ch == '\t' || ch == '\r' ||
             ch == '\v' || ch == '\f');

    while (ch >= '0' && ch <= '9') {
        uintmax_t digit = (uintmax_t)(ch - '0');
        saw_digit = 1;

        if (value > (UINT64_MAX - digit) / UINTMAX_C(10)) {
            overflow = 1;
        } else if (!overflow) {
            value = value * UINTMAX_C(10) + digit;
        }

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    }

    while (ch == ' ' || ch == '\t' || ch == '\r' ||
           ch == '\v' || ch == '\f') {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    }

    if (ch != '\n' && ch != EOF) {
        trailing = 1;
        do {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            ch = fgetc(stdin);
        } while (ch != '\n' && ch != EOF);
    }

    if (!saw_digit || overflow || trailing) {
        return 0;
    }

    *result = (uint64_t)value;
    return 1;
}

int main(void)
{
    uint64_t value;

    if (!read_uint64(&value)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", max_exchange_sum(value)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}