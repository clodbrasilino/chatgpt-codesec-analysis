#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

unsigned int highest_power_of_2(unsigned int n) {
    if (n == 0) {
        return 0;
    }
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    return n - (n >> 1);
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <positive_integer>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr;
    errno = 0;
    unsigned long val = strtoul(argv[1], &endptr, 10);
    if (*endptr != '\0' || errno == ERANGE || val > UINT_MAX) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    unsigned int result = highest_power_of_2((unsigned int)val);
    printf("%u\n", result);
    return EXIT_SUCCESS;
}