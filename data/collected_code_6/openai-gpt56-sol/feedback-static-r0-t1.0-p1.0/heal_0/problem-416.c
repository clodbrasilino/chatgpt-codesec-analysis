#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t max_exchange_sum(uint64_t number)
{
    if (number < 12U) {
        return number;
    }

    uint64_t divided_sum = max_exchange_sum(number / 2U) +
                           max_exchange_sum(number / 3U) +
                           max_exchange_sum(number / 4U);

    return divided_sum > number ? divided_sum : number;
}

int main(void)
{
    uint64_t number;

    if (scanf("%" SCNu64, &number) != 1) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", max_exchange_sum(number));
    return EXIT_SUCCESS;
}