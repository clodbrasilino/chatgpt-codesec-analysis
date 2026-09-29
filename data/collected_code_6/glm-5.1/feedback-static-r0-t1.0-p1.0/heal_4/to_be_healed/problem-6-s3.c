#include <stdio.h>
#include <stdlib.h>

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

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[const]) {
    if (argc != 3) {
        return 1;
    }
    unsigned int a = (unsigned int)strtoul(argv[1], NULL, 10);
    unsigned int b = (unsigned int)strtoul(argv[2], NULL, 10);

    int result = differ_at_one_bit(a, b);
    printf("%d\n", result);
    return 0;
}