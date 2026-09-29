#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

unsigned int toggle_odd_bits(unsigned int num) {
    return num ^ 0xAAAAAAAA;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    unsigned int num;
    
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    
    char *endptr;
    unsigned long val = strtoul(argv[1], &endptr, 0);
    
    if (*endptr != '\0' || val > UINT_MAX) {
        return EXIT_FAILURE;
    }
    
    num = (unsigned int)val;
    unsigned int result = toggle_odd_bits(num);
    printf("%u\n", result);
    
    return EXIT_SUCCESS;
}