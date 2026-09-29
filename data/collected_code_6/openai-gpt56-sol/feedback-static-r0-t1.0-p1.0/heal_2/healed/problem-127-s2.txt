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
    char *input = NULL;
    size_t capacity = 0;
    ssize_t length;
    char *current;
    char *end;
    intmax_t lhs_value;
    intmax_t rhs_value;
    int32_t result;

    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    current = input;

    errno = 0;
    lhs_value = strtoimax(current, &end, 10);
    if (current == end || errno == ERANGE ||
        lhs_value < INT32_MIN || lhs_value > INT32_MAX) {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    current = end;
    errno = 0;
    rhs_value = strtoimax(current, &end, 10);
    if (current == end || errno == ERANGE ||
        rhs_value < INT32_MIN || rhs_value > INT32_MAX) {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' || *end == '\n' ||
           *end == '\v' || *end == '\f') {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!multiply_int32((int32_t)lhs_value, (int32_t)rhs_value, &result)) {
        free(input);
        fputs("Multiplication overflow\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    if (printf("%" PRId32 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}