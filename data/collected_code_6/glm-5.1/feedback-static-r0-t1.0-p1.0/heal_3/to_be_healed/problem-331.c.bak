#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int count_unset_bits(unsigned int n) {
    int count = 0;
    int bits = sizeof(n) * 8;
    for (int i = 0; i < bits; i++) {
        count += !(n & 1);
        n >>= 1;
    }
    return count;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    char *endptr;
    unsigned long val = strtoul(argv[1], &endptr, 10);
    if (*endptr != '\0' || val > UINT32_MAX) {
        return EXIT_FAILURE;
    }
    unsigned int num = (unsigned int)val;
    int unset_bits = count_unset_bits(num);
    printf("%d\n", unset_bits);
    return EXIT_SUCCESS;
}