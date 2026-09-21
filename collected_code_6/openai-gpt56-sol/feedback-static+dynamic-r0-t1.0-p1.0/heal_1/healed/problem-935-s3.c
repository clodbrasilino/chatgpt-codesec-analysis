#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>

static int sum_of_squares(uint64_t n, uint64_t *result)
{
    uint64_t a;
    uint64_t b;
    uint64_t c;

    if (result == NULL || n > UINT64_C(3024616)) {
        return -1;
    }

    a = n;
    b = n + UINT64_C(1);
    c = UINT64_C(2) * n + UINT64_C(1);

    if (a % UINT64_C(2) == 0) {
        a /= UINT64_C(2);
    } else {
        b /= UINT64_C(2);
    }

    if (a % UINT64_C(3) == 0) {
        a /= UINT64_C(3);
    } else if (b % UINT64_C(3) == 0) {
        b /= UINT64_C(3);
    } else {
        c /= UINT64_C(3);
    }

    *result = a * b * c;
    return 0;
}

int main(void)
{
    char *line = NULL;
    char *end;
    size_t capacity = 0;
    ssize_t length;
    uintmax_t parsed;
    uint64_t result;

    length = getline(&line, &capacity, stdin);
    if (length < 0) {
        free(line);
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed = strtoumax(line, &end, 10);

    if (errno == ERANGE || end == line) {
        free(line);
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0' || parsed > UINT64_MAX) {
        free(line);
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    free(line);

    if (sum_of_squares((uint64_t)parsed, &result) != 0) {
        fputs("Input is too large.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}