#include <ctype.h>
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

static int parse_uint32(const char **input, uint32_t *value)
{
    char *end = NULL;
    uintmax_t parsed;

    while (isspace((unsigned char)**input)) {
        ++(*input);
    }

    if (**input == '\0' || **input == '-') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(*input, &end, 10);

    if (end == *input || errno == ERANGE || parsed > UINT32_MAX) {
        return 0;
    }

    *value = (uint32_t)parsed;
    *input = end;
    return 1;
}

int main(void)
{
    uint32_t first;
    uint32_t second;
    int trailing;

    if (scanf("%" SCNu32 " %" SCNu32, &first, &second) != 2) {
        return EXIT_FAILURE;
    }

    do {
        trailing = getchar();
    } while (trailing != EOF && isspace((unsigned char)trailing));

    if (trailing != EOF) {
        return EXIT_FAILURE;
    }

    if (printf("%u\n", hamming_distance(first, second)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}