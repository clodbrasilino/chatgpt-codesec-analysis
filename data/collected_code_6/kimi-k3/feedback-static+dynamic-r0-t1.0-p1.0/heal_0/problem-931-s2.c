#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

long long sum_of_cubes(int n) {
    long long sum = 0;
    int i;
    
    if (n < 1) {
        return 0;
    }
    
    for (i = 1; i <= n; i++) {
        long long cube = (long long)i * i * i;
        if (sum > LLONG_MAX - cube) {
            return -1;
        }
        sum += cube;
    }
    
    return sum;
}

int main(void) {
    char buffer[256];
    char *endptr;
    long input_val;
    int n;
    long long result;
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    errno = 0;
    input_val = strtol(buffer, &endptr, 10);
    
    if (errno != 0 || endptr == buffer || (*endptr != '\n' && *endptr != '\0')) {
        fprintf(stderr, "Invalid input format\n");
        return EXIT_FAILURE;
    }
    
    if (input_val < 1 || input_val > INT_MAX) {
        fprintf(stderr, "Input out of valid range\n");
        return EXIT_FAILURE;
    }
    
    n = (int)input_val;
    result = sum_of_cubes(n);
    
    if (result == -1) {
        fprintf(stderr, "Integer overflow occurred\n");
        return EXIT_FAILURE;
    }
    
    printf("%lld\n", result);
    
    return EXIT_SUCCESS;
}