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
    char input[128];
    char *current;
    char *end;
    uintmax_t first_value;
    uintmax_t second_value;

    if (fgets(input, sizeof input, stdin) == NULL) {
        (void)fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    current = input;
    errno = 0;
    first_value = strtoumax(current, &end, 10);

    if (current == end || errno == ERANGE || first_value > UINT32_MAX) {
        (void)fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    current = end;
    errno = 0;
    second_value = strtoumax(current, &end, 10);

    if (current == end || errno == ERANGE || second_value > UINT32_MAX) {
        (void)fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        (void)fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (printf("%u\n", hamming_distance((uint32_t)first_value,
                                        (uint32_t)second_value)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}