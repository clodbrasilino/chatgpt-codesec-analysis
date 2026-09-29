#include <stdio.h>
#include <stdlib.h>

int canBeSumOfNonZeroPowersOf2(unsigned int n) {
    if (n == 0) {
        return 0;
    }
    while (n > 0) {
        if ((n & 1) == 1) {
            n >>= 1;
            if ((n & 1) == 0) {
                return 0;
            }
        } else {
            n >>= 1;
        }
    }
    return 1;
}

int main(int argc, char * const * const argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return EXIT_FAILURE;
    }
    const char * const input = argv[1];
    char *endptr;
    unsigned long val = strtoul(input, &endptr, 10);
    if (*endptr != '\0' || val > 0xFFFFFFFFUL) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    int result = canBeSumOfNonZeroPowersOf2((unsigned int)val);
    printf("%d\n", result);
    return EXIT_SUCCESS;
}