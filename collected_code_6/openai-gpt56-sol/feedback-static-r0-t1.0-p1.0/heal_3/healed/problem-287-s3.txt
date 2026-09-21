#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_even_squares(uint64_t n, uint64_t *result)
{
    uint64_t a;
    uint64_t b;
    uint64_t c;
    uint64_t product;

    if (result == NULL || n > UINT64_MAX / 2U) {
        return 0;
    }

    a = n;
    b = n + 1U;
    c = (2U * n) + 1U;

    if ((a & 1U) == 0U) {
        a /= 2U;
    } else {
        b /= 2U;
    }

    if (a % 3U == 0U) {
        a /= 3U;
    } else if (b % 3U == 0U) {
        b /= 3U;
    } else {
        c /= 3U;
    }

    if (a != 0U && b > UINT64_MAX / a) {
        return 0;
    }

    product = a * b;

    if (product != 0U && c > UINT64_MAX / product) {
        return 0;
    }

    product *= c;

    if (product > UINT64_MAX / 4U) {
        return 0;
    }

    *result = product * 4U;
    return 1;
}

int main(void)
{
    char *line;
    char *end;
    uintmax_t value;
    uint64_t sum;
    size_t capacity;
    ssize_t length;

    line = NULL;
    capacity = 0U;

    if (printf("Enter n: ") < 0 || fflush(stdout) == EOF) {
        free(line);
        return EXIT_FAILURE;
    }

    length = getline(&line, &capacity, stdin);
    if (length < 0) {
        fprintf(stderr, "Invalid input\n");
        free(line);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = line;
    value = strtoumax(line, &end, 10);

    if (end == line || errno == ERANGE || value > UINT64_MAX) {
        fprintf(stderr, "Invalid input\n");
        free(line);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end == '\n') {
        ++end;
    }

    if (*end != '\0') {
        fprintf(stderr, "Invalid input\n");
        free(line);
        return EXIT_FAILURE;
    }

    if (!sum_even_squares((uint64_t)value, &sum)) {
        fprintf(stderr, "Result exceeds the supported range\n");
        free(line);
        return EXIT_FAILURE;
    }

    free(line);

    if (printf("%" PRIu64 "\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}