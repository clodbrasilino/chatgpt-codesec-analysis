#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t max_exchange_sum(uint64_t number)
{
    if (number < UINT64_C(12)) {
        return number;
    }

    uint64_t half = max_exchange_sum(number / UINT64_C(2));
    uint64_t third = max_exchange_sum(number / UINT64_C(3));
    uint64_t quarter = max_exchange_sum(number / UINT64_C(4));

    if (UINT64_MAX - half < third) {
        return UINT64_MAX;
    }

    uint64_t sum = half + third;

    if (UINT64_MAX - sum < quarter) {
        return UINT64_MAX;
    }

    sum += quarter;
    return sum > number ? sum : number;
}

int main(void)
{
    char *line = NULL;
    size_t capacity = 0;
    ssize_t length = getline(&line, &capacity, stdin);

    if (length < 0) {
        free(line);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    char *end = NULL;
    uintmax_t value = strtoumax(line, &end, 10);

    if (end == line || errno == ERANGE || value > UINT64_MAX) {
        free(line);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(line);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    free(line);

    uint64_t result = max_exchange_sum((uint64_t)value);
    printf("%" PRIu64 "\n", result);

    return EXIT_SUCCESS;
}