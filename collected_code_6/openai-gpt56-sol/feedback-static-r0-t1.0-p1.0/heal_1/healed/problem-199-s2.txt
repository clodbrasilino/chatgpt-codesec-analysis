#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

static uint64_t highest_power_of_two(uint64_t number)
{
    if (number == UINT64_C(0)) {
        return UINT64_C(0);
    }

    uint64_t result = UINT64_C(1);

    while (result <= number / UINT64_C(2)) {
        result *= UINT64_C(2);
    }

    return result;
}

int main(void)
{
    char input[128];
    uint64_t number;
    char extra;

    if (fgets(input, sizeof input, stdin) == NULL ||
        sscanf(input, " %" SCNu64 " %c", &number, &extra) != 1) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    printf("%" PRIu64 "\n", highest_power_of_two(number));
    return 0;
}