#include <stdio.h>
#include <stdlib.h>

static unsigned int hamming_distance(int first, int second)
{
    unsigned int difference = (unsigned int)first ^ (unsigned int)second;
    unsigned int distance = 0U;

    while (difference != 0U) {
        distance += difference & 1U;
        difference >>= 1U;
    }

    return distance;
}

int main(void)
{
    int first;
    int second;

    if (scanf("%d %d", &first, &second) != 2) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%u\n", hamming_distance(first, second));
    return EXIT_SUCCESS;
}