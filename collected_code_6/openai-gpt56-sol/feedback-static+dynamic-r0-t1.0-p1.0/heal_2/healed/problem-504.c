#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int cube_sum(uint64_t n, uint64_t *result)
{
    uint64_t a;
    uint64_t b;
    uint64_t product;

    if (result == NULL || n > UINT64_C(92681)) {
        return 0;
    }

    if ((n & UINT64_C(1)) == 0) {
        a = n / UINT64_C(2);
        b = n + UINT64_C(1);
    } else {
        a = n;
        b = (n + UINT64_C(1)) / UINT64_C(2);
    }

    product = a * b;
    *result = product * product;
    return 1;
}

int main(void)
{
    char *buffer = NULL;
    size_t capacity = 0;
    ssize_t length;
    char *end;
    uintmax_t value;
    uint64_t result;

    length = getline(&buffer, &capacity, stdin);
    if (length < 0) {
        free(buffer);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    value = strtoumax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || value > UINT64_MAX) {
        free(buffer);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(buffer);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    free(buffer);

    if (!cube_sum((uint64_t)value, &result)) {
        fputs("Input is out of range\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}