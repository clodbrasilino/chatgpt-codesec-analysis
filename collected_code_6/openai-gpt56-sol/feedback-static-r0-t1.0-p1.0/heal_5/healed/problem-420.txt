#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int cube_sum_even(uint64_t n, uint64_t *result)
{
    uint64_t half;
    uint64_t product;

    if (result == NULL || n > UINT64_C(55108)) {
        return 0;
    }

    if ((n & UINT64_C(1)) == 0) {
        half = n / UINT64_C(2);
        product = half * (n + UINT64_C(1));
    } else {
        half = (n + UINT64_C(1)) / UINT64_C(2);
        product = n * half;
    }

    *result = UINT64_C(8) * product * product;
    return 1;
}

static int read_uint64(uint64_t *result)
{
    char *line = NULL;
    size_t capacity = 0;
    ssize_t length;
    char *start;
    char *end;
    uintmax_t value;

    if (result == NULL) {
        return 0;
    }

    length = getline(&line, &capacity, stdin);
    if (length < 0) {
        free(line);
        return 0;
    }

    if (length > 0 && line[length - 1] == '\n') {
        line[--length] = '\0';
    }

    if (length > 0 && line[length - 1] == '\r') {
        line[--length] = '\0';
    }

    start = line;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '-' || *start == '\0') {
        free(line);
        return 0;
    }

    errno = 0;
    value = strtoumax(start, &end, 10);

    if (errno == ERANGE || end == start || value > UINT64_MAX) {
        free(line);
        return 0;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(line);
        return 0;
    }

    *result = (uint64_t)value;
    free(line);
    return 1;
}

int main(void)
{
    uint64_t n;
    uint64_t sum;

    if (!read_uint64(&n)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!cube_sum_even(n, &sum)) {
        fputs("Input is too large\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}