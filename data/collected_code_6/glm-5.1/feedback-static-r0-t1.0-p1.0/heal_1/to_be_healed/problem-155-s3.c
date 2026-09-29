#include <stdio.h>
#include <stdlib.h>

unsigned int toggle_even_bits(unsigned int num) {
    unsigned int mask = 0x55555555;
    return num ^ mask;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }

    char *endptr;
    unsigned long val = strtoul(argv[1], &endptr, 10);

    /* Possible weaknesses found:
     *  each undeclared identifier is reported only once for each function it appears in
     *  use of undeclared identifier '__UINT_MAX__'
     *  '__UINT_MAX__' undeclared (first use in this function); did you mean 'UINTMAX_C'?
     */
    if (*endptr != '\0' || val > __UINT_MAX__) {
        return EXIT_FAILURE;
    }

    unsigned int num = (unsigned int)val;
    unsigned int result = toggle_even_bits(num);

    printf("%u\n", result);

    return EXIT_SUCCESS;
}