#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

unsigned long long calculate_pell(int n) {
    if (n < 0) {
        return 0;
    }
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    unsigned long long a = 0;
    unsigned long long b = 1;
    for (int i = 2; i <= n; i++) {
        unsigned long long c = 2 * b + a;
        a = b;
        b = c;
    }
    return b;
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
    if (endptr == argv[1] || *endptr != '\0' || errno == ERANGE || val < 0) {
        return EXIT_FAILURE;
    }
    int n = (int)val;
    unsigned long long result = calculate_pell(n);
    printf("%llu\n", result);
    return EXIT_SUCCESS;
}