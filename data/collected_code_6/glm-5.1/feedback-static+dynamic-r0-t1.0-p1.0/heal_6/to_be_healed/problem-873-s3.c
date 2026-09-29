#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>

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
    /* Possible weaknesses found:
     *  The scope of the variable 'c' can be reduced. [variableScope]
     */
    long long a = 0, b = 1, c;
    for (int i = 2; i <= n; i++) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    int n;
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <integer>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    char *endptr;
    errno = 0;
    long val = strtol(argv[1], &endptr, 10);
    if (endptr == argv[1] || *endptr != '\0' || errno == ERANGE || val < INT_MIN || val > INT_MAX) {
        fprintf(stderr, "Invalid integer input\n");
        return EXIT_FAILURE;
    }
    n = (int)val;
    
    long long result = fibonacci(n);
    printf("%lld\n", result);
    
    return EXIT_SUCCESS;
}