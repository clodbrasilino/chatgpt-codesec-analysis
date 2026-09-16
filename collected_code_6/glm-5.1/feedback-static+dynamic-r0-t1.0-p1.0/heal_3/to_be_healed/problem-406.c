#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int find_parity(unsigned int n) {
    int parity = 0;
    while (n) {
        parity ^= (n & 1);
        n >>= 1;
    }
    return parity;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <unsigned_integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    errno = 0;
    unsigned long val = strtoul(argv[1], &endptr, 10);
    
    if (errno == ERANGE || val > 0xFFFFFFFF || *endptr != '\0') {
        fprintf(stderr, "Invalid input or value out of range for 32-bit unsigned integer\n");
        return EXIT_FAILURE;
    }

    unsigned int num = (unsigned int)val;
    int result = find_parity(num);

    printf("%d\n", result);
    return EXIT_SUCCESS;
}