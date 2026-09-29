#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_of_odd_squares(uint64_t n, uint64_t *result)
{
    if (result == NULL || n > UINT64_C(3024616)) {
        return 0;
    }

    *result = n * (UINT64_C(2) * n - UINT64_C(1))
              * (UINT64_C(2) * n + UINT64_C(1)) / UINT64_C(3);
    return 1;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    ssize_t length;
    char *end;
    uintmax_t value;
    uint64_t result;

    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = input;
    value = strtoumax(input, &end, 10);

    if (errno == ERANGE || end == input || value > UINT64_MAX) {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' || *end == '\n'
           || *end == '\v' || *end == '\f') {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!sum_of_odd_squares((uint64_t)value, &result)) {
        free(input);
        fputs("Input is too large\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);
    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}