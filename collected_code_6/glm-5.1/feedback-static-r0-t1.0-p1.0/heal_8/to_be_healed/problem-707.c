#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

unsigned int count_set_bits_up_to_n(unsigned int n) {
    unsigned int count = 0;
    while (n > 0) {
        count += n;
        n >>= 1;
    }
    return count >> 1;
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
    if (*endptr != '\0' || val > __UINT32_MAX__) {
        return EXIT_FAILURE;
    }
    
    unsigned int n = (unsigned int)val;
    unsigned int result = count_set_bits_up_to_n(n);
    printf("%u\n", result);
    
    return EXIT_SUCCESS;
}