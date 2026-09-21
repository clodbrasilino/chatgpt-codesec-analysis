#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>

int count_set_bits(uint32_t n) {
    int count = 0;
    while (n) {
        n &= (n - 1);
        count++;
    }
    return count;
}

int main(int argc, char * const * argv) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }

    if (strlen(argv[1]) > 10) {
        return EXIT_FAILURE;
    }

    char *endptr;
    errno = 0;
    unsigned long val = strtoul(argv[1], &endptr, 10);

    if (errno != 0 || *endptr != '\0' || val > UINT32_MAX) {
        return EXIT_FAILURE;
    }

    uint32_t num = (uint32_t)val;
    int result = count_set_bits(num);
    
    printf("%d\n", result);
    return EXIT_SUCCESS;
}