#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_fifth_powers(uint64_t n, uint64_t *result)
{
    __uint128_t value;
    __uint128_t square;

    if (result == NULL) {
        return -1;
    }

    value = (__uint128_t)n * (( __uint128_t)n + 1);
    square = (__uint128_t)2 * n * n + (__uint128_t)2 * n - 1;
    value = value * square / 12;

    if (value > UINT64_MAX) {
        return -1;
    }

    *result = (uint64_t)value;
    return 0;
}

static int read_uint64(uint64_t *value)
{
    char *input = NULL;
    size_t capacity = 0;
    ssize_t length;
    char *p;
    char *end;
    uintmax_t parsed;

    if (value == NULL) {
        return -1;
    }

    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        free(input);
        return -1;
    }

    if (length > 0 && input[length - 1] == '\n') {
        input[--length] = '\0';
    } else if (!feof(stdin)) {
        free(input);
        return -1;
    }

    if (length > 0 && input[length - 1] == '\r') {
        input[length - 1] = '\0';
    }

    p = input;
    while (isspace((unsigned char)*p)) {
        ++p;
    }

    if (*p == '\0' || *p == '-') {
        free(input);
        return -1;
    }

    errno = 0;
    parsed = strtoumax(p, &end, 10);

    if (errno == ERANGE || end == p) {
        free(input);
        return -1;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0' || parsed > UINT64_MAX) {
        free(input);
        return -1;
    }

    *value = (uint64_t)parsed;
    free(input);
    return 0;
}

int main(void)
{
    uint64_t n;
    uint64_t sum;

    if (read_uint64(&n) != 0) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (sum_fifth_powers(n, &sum) != 0) {
        fputs("Result out of range\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}