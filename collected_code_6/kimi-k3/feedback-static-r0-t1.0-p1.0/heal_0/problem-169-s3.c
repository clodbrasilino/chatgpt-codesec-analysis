#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

long long pell(int n) {
    if (n < 0) {
        return -1;
    }
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    
    long long prev2 = 0;
    long long prev1 = 1;
    long long current = 0;
    
    for (int i = 2; i <= n; i++) {
        if (prev1 > (LLONG_MAX - prev2) / 2) {
            return -1;
        }
        current = 2 * prev1 + prev2;
        prev2 = prev1;
        prev1 = current;
    }
    
    return current;
}

int main(void) {
    char input[32];
    char *endptr;
    long val;
    int n;
    
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    errno = 0;
    val = strtol(input, &endptr, 10);
    
    if (errno != 0 || endptr == input || *endptr != '\n' && *endptr != '\0') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (val < 0 || val > 90) {
        fprintf(stderr, "Input out of range\n");
        return EXIT_FAILURE;
    }
    
    n = (int)val;
    long long result = pell(n);
    
    if (result == -1 && n > 1) {
        fprintf(stderr, "Overflow occurred\n");
        return EXIT_FAILURE;
    }
    
    printf("%lld\n", result);
    
    return EXIT_SUCCESS;
}