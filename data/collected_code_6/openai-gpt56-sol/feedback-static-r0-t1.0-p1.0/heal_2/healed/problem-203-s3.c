#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static unsigned int hamming_distance(uint32_t first, uint32_t second)
{
    uint32_t difference = first ^ second;
    unsigned int distance = 0U;

    while (difference != UINT32_C(0)) {
        difference &= difference - UINT32_C(1);
        ++distance;
    }

    return distance;
}

int main(void)
{
    uintmax_t first_value;
    uintmax_t second_value;
    int result;
    int ch;

    errno = 0;
    result = scanf("%" SCNuMAX " %" SCNuMAX, &first_value, &second_value);

    if (result != 2 || errno == ERANGE ||
        first_value > UINT32_MAX || second_value > UINT32_MAX) {
        (void)fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    do {
        ch = getchar();
    } while (ch == ' ' || ch == '\t' || ch == '\n' ||
             ch == '\r' || ch == '\f' || ch == '\v');

    if (ch != EOF) {
        (void)fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (printf("%u\n", hamming_distance((uint32_t)first_value,
                                        (uint32_t)second_value)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}