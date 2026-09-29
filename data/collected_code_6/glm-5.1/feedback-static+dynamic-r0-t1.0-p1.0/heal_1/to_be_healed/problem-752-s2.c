#include <stdio.h>
#include <stdlib.h>

unsigned long long jacobsthal(int n) {
    if (n < 0) {
        exit(EXIT_FAILURE);
    }
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    
    unsigned long long prev2 = 0;
    unsigned long long prev1 = 1;
    unsigned long long current = 0;
    
    for (int i = 2; i <= n; i++) {
        current = prev1 + (prev2 << 1);
        prev2 = prev1;
        prev1 = current;
    }
    
    return current;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    long val = strtol(argv[1], NULL, 10);
    if (val < 0 || val > 61) {
        fprintf(stderr, "n must be between 0 and 61 inclusive\n");
        return EXIT_FAILURE;
    }
    
    unsigned long long result = jacobsthal((int)val);
    printf("%llu\n", result);
    
    return EXIT_SUCCESS;
}