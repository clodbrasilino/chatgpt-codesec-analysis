#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

long long fibonacci(int n) {
    if (n < 0) {
        exit(EXIT_FAILURE);
    }
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
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
    
    if (endptr == argv[1] || *endptr != '\0' || errno == ERANGE || val < 0 || val > INT_MAX) {
        return EXIT_FAILURE;
    }
    
    int n = (int)val;
    long long result = fibonacci(n);
    printf("%lld\n", result);
    return EXIT_SUCCESS;
}