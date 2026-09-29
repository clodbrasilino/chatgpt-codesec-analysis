#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

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
int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    unsigned long val = strtoul(argv[1], &endptr, 10);

    if (*endptr != '\0' || val > UINT_MAX) {
        fprintf(stderr, "Invalid input or out of range.\n");
        return EXIT_FAILURE;
    }

    int result = check_even_parity((unsigned int)val);
    printf("%d\n", result);

    return EXIT_SUCCESS;
}