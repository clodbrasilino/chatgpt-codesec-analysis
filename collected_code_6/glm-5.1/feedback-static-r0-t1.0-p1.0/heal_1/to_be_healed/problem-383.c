#include <stdio.h>
#include <stdlib.h>

unsigned int toggle_odd_bits(unsigned int num) {
    unsigned int mask = 0xAAAAAAAA;
    return num ^ mask;
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
    unsigned long val = strtoul(argv[1], &endptr, 0);

    if (*endptr != '\0' || val > 0xFFFFFFFFUL) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    unsigned int result = toggle_odd_bits((unsigned int)val);
    printf("%u\n", result);

    return EXIT_SUCCESS;
}