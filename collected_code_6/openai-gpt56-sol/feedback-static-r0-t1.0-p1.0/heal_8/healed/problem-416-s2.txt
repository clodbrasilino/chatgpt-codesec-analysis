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

static void discard_line(int ch)
{
    while (ch != '\n' && ch != EOF) {
        ch = fgetc(stdin);
    }
}

static int read_uint64(uint64_t *result)
{
    uint64_t value = 0;
    int ch;
    int saw_digit = 0;
    int overflow = 0;

    if (result == NULL) {
        return 0;
    }

    do {
        ch = fgetc(stdin);
    } while (is_horizontal_space(ch));

    while (ch >= '0' && ch <= '9') {
        uint64_t digit = (uint64_t)(ch - '0');
        saw_digit = 1;

        if (!overflow) {
            if (value > (UINT64_MAX - digit) / UINT64_C(10)) {
                overflow = 1;
            } else {
                value = value * UINT64_C(10) + digit;
            }
        }

        ch = fgetc(stdin);
    }

    while (is_horizontal_space(ch)) {
        ch = fgetc(stdin);
    }

    if (ch != '\n' && ch != EOF) {
        discard_line(ch);
        return 0;
    }

    if (!saw_digit || overflow) {
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