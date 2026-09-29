#include <stdio.h>
#include <stdlib.h>

static unsigned int hamming_distance(unsigned int first, unsigned int second)
{
    unsigned int value = first ^ second;
    unsigned int distance = 0U;

    while (value != 0U) {
        value &= value - 1U;
        ++distance;
    }

    return distance;
}

int main(void)
{
    unsigned int first = 0U;
    unsigned int second = 0U;

    if (scanf("%u %u", &first, &second) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    printf("%u\n", hamming_distance(first, second));
    return EXIT_SUCCESS;
}