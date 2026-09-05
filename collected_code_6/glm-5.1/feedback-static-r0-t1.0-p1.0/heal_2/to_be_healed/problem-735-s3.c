#include <stdio.h>
#include <stdlib.h>

unsigned int toggle_middle_bits(unsigned int num) {
    if (num <= 1) {
        return num;
    }
    unsigned int mask = 0xFFFFFFFC;
    mask = (mask >> (__builtin_clz(num) + 1)) << 1;
    return num ^ mask;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 2) {
        return 1;
    }
    char *endptr;
    unsigned int num = strtoul(argv[1], &endptr, 10);
    if (*endptr != '\0') {
        return 1;
    }
    unsigned int result = toggle_middle_bits(num);
    printf("%u\n", result);
    return 0;
}