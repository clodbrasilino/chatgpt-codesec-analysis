#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <inttypes.h>
#include <string.h>
#include <errno.h>

int count_set_bits(unsigned int n) {
    int count = 0;
    while (n) {
        count += n & 1;
        n >>= 1;
    }
    return count;
}

int main(int argc, char * const * argv) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }

    size_t len = strnlen(argv[1], 11);
    if (len == 0 || len > 10) {
        return EXIT_FAILURE;
    }

    char *endptr;
    errno = 0;
    unsigned long val = strtoul(argv[1], &endptr, 10);

    if (errno != 0 || *endptr != '\0' || val > UINT32_MAX) {
        return EXIT_FAILURE;
    }

    unsigned int num = (unsigned int)val;
    int result = count_set_bits(num);

    printf("%d\n", result);
    return EXIT_SUCCESS;
}