#include <stdio.h>
#include <stdlib.h>

static unsigned long long highest_power_of_two(unsigned long long number)
{
    unsigned long long result = 1;

    if (number == 0) {
        return 0;
    }

    while (result <= number / 2) {
        result *= 2;
    }

    return result;
}

int main(void)
{
    unsigned long long number;
    int result;

    result = scanf("%llu", &number);
    if (result != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    printf("%llu\n", highest_power_of_two(number));
    return EXIT_SUCCESS;
}