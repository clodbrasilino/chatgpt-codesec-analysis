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

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr;
    unsigned long val = strtoul(argv[1], &endptr, 10);
    if (*endptr != '\0' || val > 0xFFFFFFFFUL) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    int result = canBeSumOfNonZeroPowersOf2((unsigned int)val);
    printf("%d\n", result);
    return EXIT_SUCCESS;
}