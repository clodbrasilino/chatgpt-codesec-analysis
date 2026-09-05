#include <stdio.h>
#include <stdlib.h>

int check_even_parity(unsigned int num) {
    int count = 0;
    while (num) {
        count ^= (num & 1);
        num >>= 1;
    }
    return count == 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
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
        fprintf(stderr, "Invalid input or out of range.\n");
        return EXIT_FAILURE;
    }

    int result = check_even_parity((unsigned int)val);
    printf("%d\n", result);

    return EXIT_SUCCESS;
}