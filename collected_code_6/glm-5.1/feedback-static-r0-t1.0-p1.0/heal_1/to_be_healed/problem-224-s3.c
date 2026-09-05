#include <stdio.h>
#include <stdlib.h>

unsigned int count_set_bits(unsigned int n) {
    unsigned int count = 0;
    while (n) {
        count += n & 1;
        n >>= 1;
    }
    return count;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <positive_integer>\n", argv[0]);
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
        fprintf(stderr, "Error: Invalid input. Must be a valid unsigned integer.\n");
        return EXIT_FAILURE;
    }

    unsigned int num = (unsigned int)val;
    unsigned int result = count_set_bits(num);

    printf("%u\n", result);
    return EXIT_SUCCESS;
}