#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

int nth_polite_number(int n) {
    if (n <= 0) {
        exit(EXIT_FAILURE);
    }
    int bit_count = 0;
    int temp = n;
    while (temp > 0) {
        if (temp & 1) {
            bit_count++;
        }
        temp >>= 1;
    }
    return n + bit_count;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    char *endptr;
    errno = 0;
    long val = strtol(argv[1], &endptr, 10);
    if (errno != 0 || endptr == argv[1] || *endptr != '\0' || val <= 0 || val > INT_MAX) {
        return EXIT_FAILURE;
    }
    int n = (int)val;
    int result = nth_polite_number(n);
    printf("%d\n", result);
    return EXIT_SUCCESS;
}