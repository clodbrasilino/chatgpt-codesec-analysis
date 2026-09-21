#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int calculate_difference(uint64_t n, uint64_t *result)
{
    if (result == NULL || n == UINT64_MAX) {
        return 0;
    }

    uint64_t a = n;
    uint64_t b = n + UINT64_C(1);

    if ((a & UINT64_C(1)) == 0) {
        a /= UINT64_C(2);
    } else {
        b /= UINT64_C(2);
    }

    if (a != 0 && b > UINT64_MAX / a) {
        return 0;
    }

    uint64_t sum = a * b;

    if (sum != 0 && sum > UINT64_MAX / sum) {
        return 0;
    }

    uint64_t square = sum * sum;
    *result = square - sum;
    return 1;
}

static int discard_line(void)
{
    int ch;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != '\n' && ch != EOF) {
    }

    return ch;
}

static int read_uint64(uint64_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];

    if (value == NULL) {
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
        discard_line();
        return 0;
    }

    size_t pos = 0;
    while (buffer[pos] == ' ' || buffer[pos] == '\t' ||
           buffer[pos] == '\r' || buffer[pos] == '\f' ||
           buffer[pos] == '\v') {
        ++pos;
    }

    if (buffer[pos] == '\0' || buffer[pos] == '\n' ||
        buffer[pos] == '+' || buffer[pos] == '-') {
        return 0;
    }

    uint64_t number = 0;
    int has_digit = 0;

    while (buffer[pos] >= '0' && buffer[pos] <= '9') {
        uint64_t digit = (uint64_t)(buffer[pos] - '0');

        if (number > (UINT64_MAX - digit) / UINT64_C(10)) {
            return 0;
        }

        number = number * UINT64_C(10) + digit;
        has_digit = 1;
        ++pos;
    }

    if (!has_digit) {
        return 0;
    }

    while (buffer[pos] == ' ' || buffer[pos] == '\t' ||
           buffer[pos] == '\r' || buffer[pos] == '\f' ||
           buffer[pos] == '\v') {
        ++pos;
    }

    if (buffer[pos] != '\0' && buffer[pos] != '\n') {
        return 0;
    }

    *value = number;
    return 1;
}

int main(void)
{
    uint64_t n;
    uint64_t difference;

    if (!read_uint64(&n)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!calculate_difference(n, &difference)) {
        fputs("Result is out of range\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", difference) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}