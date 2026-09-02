#include <stdio.h>
#include <stdlib.h>

long long hexagonal_number(int n) {
    if (n <= 0) {
        return -1;
    }
    return (long long)n * (2 * (long long)n - 1);
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    int n;
    
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    
    if (*endptr != '\0' || endptr == argv[1]) {
        fprintf(stderr, "Error: Invalid integer input\n");
        return EXIT_FAILURE;
    }
    
    if (val > 2147483647 || val < -2147483648) {
        fprintf(stderr, "Error: Integer overflow\n");
        return EXIT_FAILURE;
    }
    
    n = (int)val;
    
    long long result = hexagonal_number(n);
    
    if (result == -1) {
        fprintf(stderr, "Error: n must be positive\n");
        return EXIT_FAILURE;
    }
    
    printf("%lld\n", result);
    
    return EXIT_SUCCESS;
}