#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int differ_at_one_bit(unsigned int a, unsigned int b) {
    unsigned int xor = a ^ b;
    if (xor == 0) {
        return 0;
    }
    unsigned int mask = xor - 1;
    if ((xor & mask) == 0) {
        return 1;
    }
    return 0;
}

int main(int argc, char * const * const argv) {
    if (argc != 3) {
        return 1;
    }
    char *endptr;
    unsigned long val_a = strtoul(argv[1], &endptr, 10);
    if (*endptr != '\0' || val_a > UINT_MAX) {
        return 1;
    }
    unsigned long val_b = strtoul(argv[2], &endptr, 10);
    if (*endptr != '\0' || val_b > UINT_MAX) {
        return 1;
    }
    unsigned int a = (unsigned int)val_a;
    unsigned int b = (unsigned int)val_b;

    int result = differ_at_one_bit(a, b);
    printf("%d\n", result);
    return 0;
}