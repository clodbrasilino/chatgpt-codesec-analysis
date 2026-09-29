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
    char input[128];
    char extra;
    char *end;
    uintmax_t value;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoumax(input, &end, 10);

    if (end == input || errno == ERANGE || value > UINT64_MAX) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' || *end == '\n' ||
           *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0' || sscanf(input, " %*ju %c", &extra) == 1) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    uint64_t number = (uint64_t)value;
    printf("%" PRIu64 "\n", max_exchange_sum(number));

    return EXIT_SUCCESS;
}