#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static int most_significant_set_bit(unsigned int value)
{
    int bit = 0;

    if (value == 0U) {
        return -1;
    }

    while (value >>= 1U) {
        ++bit;
    }

    return bit;
}

int main(void)
{
    unsigned int value;

    if (scanf("%u", &value) != 1) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    const int bit = most_significant_set_bit(value);

    if (bit < 0) {
        fputs("No set bit\n", stdout);
    } else {
        printf("%d\n", bit);
    }

    return EXIT_SUCCESS;
}