#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long nth_nonagonal(int n) {
    if (n < 1) {
        return -1;
    }
    long long result = (long long)n * (7LL * n - 5) / 2;
    if (result < 0) {
        return -1;
    }
    return result;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[]) {
    int n;
    
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return 1;
    }
    
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    
    if (*endptr != '\0' || endptr == argv[1] || val < 1 || val > INT_MAX) {
        fprintf(stderr, "Error: Invalid input. Please provide a positive integer.\n");
        return 1;
    }
    
    n = (int)val;
    long long result = nth_nonagonal(n);
    
    if (result < 0) {
        fprintf(stderr, "Error: Result overflow or invalid input.\n");
        return 1;
    }
    
    printf("%lld\n", result);
    return 0;
}