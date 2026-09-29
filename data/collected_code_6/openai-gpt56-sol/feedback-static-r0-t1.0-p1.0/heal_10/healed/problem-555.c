#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int calculate_difference(uint64_t n, uint64_t *result)
{
    uint64_t a;
    uint64_t b;
    uint64_t sum;

    if (result == NULL || n == UINT64_MAX) {
        return 0;
    }

    a = n;
    b = n + UINT64_C(1);

    if ((a & UINT64_C(1)) == 0) {
        a /= UINT64_C(2);
    } else {
        b /= UINT64_C(2);
    }

    if (a != 0 && b > UINT64_MAX / a) {
        return 0;
    }

    sum = a * b;

    if (sum != 0 && sum > UINT64_MAX / sum) {
        return 0;
    }

    *result = sum * sum - sum;
    return 1;
}

static int discard_line(void)
{
    int ch;

    do {
        ch = fgetc(stdin);
    } while (ch != '\n' && ch != EOF);

    return !ferror(stdin);
}

static int read_uint64(uint64_t *value)
{
    char buffer[128];
    uint64_t number = 0;
    size_t i = 0;
    int have_digit = 0;

    if (value == NULL) {
        return 0;
    }

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return 0;
    }

    while (buffer[i] != '\0' && buffer[i] != '\n') {
        ++i;
    }

    if (buffer[i] != '\n' && !feof(stdin)) {
        discard_line();
        return 0;
    }

    i = 0;

    while (buffer[i] == ' ' || buffer[i] == '\t' ||
           buffer[i] == '\r' || buffer[i] == '\f' ||
           buffer[i] == '\v') {
        ++i;
    }

    while (buffer[i] >= '0' && buffer[i] <= '9') {
        uint64_t digit = (uint64_t)(buffer[i] - '0');

        if (number > (UINT64_MAX - digit) / UINT64_C(10)) {
            return 0;
        }

        number = number * UINT64_C(10) + digit;
        have_digit = 1;
        ++i;
    }

    while (buffer[i] == ' ' || buffer[i] == '\t' ||
           buffer[i] == '\r' || buffer[i] == '\f' ||
           buffer[i] == '\v') {
        ++i;
    }

    if (!have_digit ||
        (buffer[i] != '\n' && buffer[i] != '\0') ||
        ferror(stdin)) {
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