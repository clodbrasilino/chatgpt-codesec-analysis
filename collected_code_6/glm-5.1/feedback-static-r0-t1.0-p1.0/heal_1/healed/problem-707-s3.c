#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

unsigned int countSetBits(unsigned int n) {
    unsigned int count = 0;
    unsigned int x = 1;
    while (x <= n) {
        unsigned int next_x = x << 1;
        if (next_x <= x) {
            break;
        }
        unsigned int full_cycles = n / next_x;
        count += full_cycles * x;
        unsigned int remainder = n % next_x;
        if (remainder >= x) {
            count += remainder - x + 1;
        }
        x = next_x;
    }
    return count;
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    char *endptr;
    unsigned long val = strtoul(argv[1], &endptr, 10);
    if (*endptr != '\0' || val > UINT_MAX) {
        return EXIT_FAILURE;
    }
    unsigned int n = (unsigned int)val;
    unsigned int result = countSetBits(n);
    printf("%u\n", result);
    return EXIT_SUCCESS;
}