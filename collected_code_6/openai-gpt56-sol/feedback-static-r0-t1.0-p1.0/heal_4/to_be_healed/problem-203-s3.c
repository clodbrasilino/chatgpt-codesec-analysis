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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    char extra;
    uintmax_t first_value;
    uintmax_t second_value;
    int result;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    result = sscanf(input, " %" SCNuMAX " %" SCNuMAX " %c",
                    &first_value, &second_value, &extra);

    if (result != 2 || errno == ERANGE ||
        first_value > UINT32_MAX || second_value > UINT32_MAX) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%u\n",
               hamming_distance((uint32_t)first_value,
                                (uint32_t)second_value)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}