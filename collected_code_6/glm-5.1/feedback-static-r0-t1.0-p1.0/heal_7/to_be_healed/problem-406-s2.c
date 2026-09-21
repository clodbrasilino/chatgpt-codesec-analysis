#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int find_parity(unsigned int num) {
    int parity = 0;
    while (num) {
        parity ^= (num & 1);
        num >>= 1;
    }
    return parity;
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
    unsigned long val = strtoul(argv[1], &endptr, 10);
    
    if (*endptr != '\0' || val > __UINT32_MAX__) {
        return EXIT_FAILURE;
    }
    
    int result = find_parity((unsigned int)val);
    
    if (printf("%d\n", result) < 0) {
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}