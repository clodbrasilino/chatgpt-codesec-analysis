#include <errno.h>
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

int main(void)
{
    char *line = NULL;
    size_t capacity = 0;
    ssize_t length;
    char *end;
    uintmax_t value;
    uint64_t difference;

    length = getline(&line, &capacity, stdin);
    if (length < 0) {
        free(line);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoumax(line, &end, 10);

    if (end == line || errno == ERANGE || value > UINT64_MAX) {
        free(line);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r') {
        ++end;
    }

    if (*end == '\n') {
        ++end;
    }

    if (*end != '\0') {
        free(line);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!calculate_difference((uint64_t)value, &difference)) {
        free(line);
        fputs("Result is out of range\n", stderr);
        return EXIT_FAILURE;
    }

    free(line);

    if (printf("%" PRIu64 "\n", difference) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}