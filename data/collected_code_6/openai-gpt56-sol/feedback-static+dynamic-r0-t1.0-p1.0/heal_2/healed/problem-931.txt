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
        return -1;
    }

    a = n;
    b = n + UINT64_C(1);

    if ((a & UINT64_C(1)) == 0) {
        a /= UINT64_C(2);
    } else {
        b /= UINT64_C(2);
    }

    if (a != 0 && b > UINT64_MAX / a) {
        return -1;
    }

    product = a * b;

    if (product != 0 && product > UINT64_MAX / product) {
        return -1;
    }

    *result = product * product;
    return 0;
}

int main(void)
{
    char *line = NULL;
    size_t capacity = 0;
    ssize_t length;
    char *end;
    uintmax_t value;
    uint64_t sum;

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
    end = NULL;
    value = strtoumax(line, &end, 10);

    if (end == line || errno == ERANGE || value > UINT64_MAX) {
        fprintf(stderr, "Invalid input\n");
        free(line);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\n' || *end == '\v' || *end == '\f') {
        ++end;
    }

    if (*end != '\0') {
        fprintf(stderr, "Invalid input\n");
        free(line);
        return EXIT_FAILURE;
    }

    free(line);

    if (sum_of_cubes((uint64_t)value, &sum) != 0) {
        fprintf(stderr, "Result exceeds the supported range\n");
        return EXIT_FAILURE;
    }

    if (printf("Sum: %" PRIu64 "\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}