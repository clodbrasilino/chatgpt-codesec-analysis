#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static int most_significant_set_bit(unsigned int value)
{
    int position = -1;

    while (value != 0U) {
        ++position;
        value >>= 1U;
    }

    return position;
}

int main(void)
{
    unsigned int value;

    if (scanf("%u", &value) != 1) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (value == 0U) {
        fputs("No set bit\n", stdout);
        return EXIT_SUCCESS;
    }

    printf("%d\n", most_significant_set_bit(value));
    return EXIT_SUCCESS;
}