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

static int is_horizontal_space(int ch)
{
    return ch == ' ' || ch == '\t' || ch == '\r' ||
           ch == '\v' || ch == '\f';
}

static int read_uint64(uint64_t *result)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];

    if (result == NULL) {
        return 0;
    }

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return 0;
    }

    size_t length = 0;
    while (buffer[length] != '\0' && buffer[length] != '\n') {
        ++length;
    }

    if (buffer[length] != '\n' && !feof(stdin)) {
        int ch;
        do {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            ch = getchar();
        } while (ch != '\n' && ch != EOF);
        return 0;
    }

    size_t position = 0;
    while (position < length &&
           is_horizontal_space((unsigned char)buffer[position])) {
        ++position;
    }

    if (position == length ||
        buffer[position] < '0' || buffer[position] > '9') {
        return 0;
    }

    uint64_t value = 0;

    while (position < length &&
           buffer[position] >= '0' && buffer[position] <= '9') {
        uint64_t digit = (uint64_t)(buffer[position] - '0');

        if (value > (UINT64_MAX - digit) / UINT64_C(10)) {
            return 0;
        }

        value = value * UINT64_C(10) + digit;
        ++position;
    }

    while (position < length &&
           is_horizontal_space((unsigned char)buffer[position])) {
        ++position;
    }

    if (position != length) {
        return 0;
    }

    *result = value;
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