#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_of_cubes(uint64_t n, uint64_t *result)
{
    uint64_t a;
    uint64_t b;
    uint64_t product;

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

    product = a * b;

    if (product != 0 && product > UINT64_MAX / product) {
        return 0;
    }

    *result = product * product;
    return 1;
}

int main(void)
{
    char *line = NULL;
    size_t capacity = 0;
    ssize_t length;
    char *end;
    uintmax_t value;
    uint64_t result;

    length = getline(&line, &capacity, stdin);
    if (length < 0) {
        free(line);
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = line;
    value = strtoumax(line, &end, 10);

    if (end == line || errno == ERANGE || value > UINT64_MAX) {
        free(line);
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(line);
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    free(line);

    if (!sum_of_cubes((uint64_t)value, &result)) {
        fputs("Result is outside the uint64_t range.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}