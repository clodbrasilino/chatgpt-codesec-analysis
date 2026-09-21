#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>

static uintmax_t gcd(uintmax_t a, uintmax_t b)
{
    while (b != 0) {
        uintmax_t remainder = a % b;
        a = b;
        b = remainder;
    }

    return a;
}

static int lcm(uintmax_t a, uintmax_t b, uintmax_t *result)
{
    uintmax_t divisor;

    if (a == 0 || b == 0 || result == NULL) {
        return -1;
    }

    divisor = gcd(a, b);

    if (a / divisor > UINTMAX_MAX / b) {
        return -1;
    }

    *result = (a / divisor) * b;
    return 0;
}

static int read_values(uintmax_t *a, uintmax_t *b)
{
    char buffer[256];
    char *cursor;
    char *end;

    if (a == NULL || b == NULL || fgets(buffer, sizeof buffer, stdin) == NULL) {
        return -1;
    }

    cursor = buffer;

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor == '-' || *cursor == '\0') {
        return -1;
    }

    errno = 0;
    *a = strtoumax(cursor, &end, 10);
    if (cursor == end || errno == ERANGE || *a == 0) {
        return -1;
    }

    cursor = end;
    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor == '-' || *cursor == '\0') {
        return -1;
    }

    errno = 0;
    *b = strtoumax(cursor, &end, 10);
    if (cursor == end || errno == ERANGE || *b == 0) {
        return -1;
    }

    cursor = end;
    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor != '\0') {
        return -1;
    }

    return 0;
}

int main(void)
{
    uintmax_t a;
    uintmax_t b;
    uintmax_t result;

    if (read_values(&a, &b) != 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (lcm(a, b, &result) != 0) {
        fprintf(stderr, "LCM cannot be represented\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIuMAX "\n", result);
    return EXIT_SUCCESS;
}