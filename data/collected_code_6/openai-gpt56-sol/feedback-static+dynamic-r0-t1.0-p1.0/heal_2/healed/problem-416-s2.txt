#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t max_exchange_sum(uint64_t n)
{
    if (n < UINT64_C(12)) {
        return n;
    }

    uint64_t half = max_exchange_sum(n / UINT64_C(2));
    uint64_t third = max_exchange_sum(n / UINT64_C(3));
    uint64_t quarter = max_exchange_sum(n / UINT64_C(4));

    if (half > UINT64_MAX - third) {
        return UINT64_MAX;
    }

    uint64_t sum = half + third;

    if (sum > UINT64_MAX - quarter) {
        return UINT64_MAX;
    }

    sum += quarter;
    return sum > n ? sum : n;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    ssize_t length = getline(&input, &capacity, stdin);

    if (length < 0) {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    char *end = NULL;
    uintmax_t value = strtoumax(input, &end, 10);

    if (errno == ERANGE || end == input || value > UINT64_MAX) {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\n' || *end == '\v' || *end == '\f') {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", max_exchange_sum((uint64_t)value));
    free(input);
    return EXIT_SUCCESS;
}