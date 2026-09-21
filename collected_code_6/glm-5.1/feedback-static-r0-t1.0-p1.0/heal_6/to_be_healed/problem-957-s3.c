#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

unsigned int rightmost_set_bit_position(int num) {
    if (num == 0) {
        return 0;
    }
    unsigned int n = (unsigned int)num;
    unsigned int isolated = n & (~n + 1);
    unsigned int pos = 0;
    while (isolated >>= 1) {
        pos++;
    }
    return pos + 1;
}

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || val < INT_MIN || val > INT_MAX) {
        return EXIT_FAILURE;
    }
    int num = (int)val;
    unsigned int res = rightmost_set_bit_position(num);
    printf("%u\n", res);
    return EXIT_SUCCESS;
}