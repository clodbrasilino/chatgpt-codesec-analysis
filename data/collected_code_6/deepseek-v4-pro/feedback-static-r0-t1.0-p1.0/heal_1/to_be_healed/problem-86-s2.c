#include <stdio.h>
#include <stdlib.h>

long long centered_hexagonal(int n) {
    if (n <= 0) {
        return -1;
    }
    return 3LL * n * (n - 1) + 1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    int n;
    
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return 1;
    }
    
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    
    if (*endptr != '\0' || endptr == argv[1]) {
        fprintf(stderr, "Error: Invalid integer\n");
        return 1;
    }
    
    if (val <= 0 || val > 1000000) {
        fprintf(stderr, "Error: n must be between 1 and 1000000\n");
        return 1;
    }
    
    n = (int)val;
    
    long long result = centered_hexagonal(n);
    
    if (result == -1) {
        fprintf(stderr, "Error: Invalid input to centered_hexagonal\n");
        return 1;
    }
    
    printf("%lld\n", result);
    
    return 0;
}