#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int multiply_int32(int32_t lhs, int32_t rhs, int32_t *result)
{
    int64_t product;

    if (result == NULL) {
        return 0;
    }

    product = (int64_t)lhs * (int64_t)rhs;

    if (product < INT32_MIN || product > INT32_MAX) {
        return 0;
    }

    *result = (int32_t)product;
    return 1;
}

int main(void)
{
    char input[128];
    char *current;
    char *end;
    intmax_t lhs_value;
    intmax_t rhs_value;
    int32_t lhs;
    int32_t rhs;
    int32_t result;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    current = input;

    errno = 0;
    lhs_value = strtoimax(current, &end, 10);
    if (current == end || errno == ERANGE ||
        lhs_value < INT32_MIN || lhs_value > INT32_MAX) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    current = end;
    errno = 0;
    rhs_value = strtoimax(current, &end, 10);
    if (current == end || errno == ERANGE ||
        rhs_value < INT32_MIN || rhs_value > INT32_MAX) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' || *end == '\n' ||
           *end == '\v' || *end == '\f') {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    lhs = (int32_t)lhs_value;
    rhs = (int32_t)rhs_value;

    if (!multiply_int32(lhs, rhs, &result)) {
        fputs("Multiplication overflow\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRId32 "\n", result);
    return EXIT_SUCCESS;
}