#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

long long cube_sum_even(int n) {
    long long sum = 0;
    int i;
    
    for (i = 1; i <= n; i++) {
        long long even_num = 2LL * i;
        
        if (even_num > 0 && even_num <= 2097151LL) {
            long long cube = even_num * even_num * even_num;
            if (sum <= LLONG_MAX - cube) {
                sum += cube;
            } else {
                break;
            }
        } else {
            break;
        }
    }
    
    return sum;
}

int main(void) {
    char buffer[256];
    char *endptr;
    long val;
    int n;
    long long result;
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    errno = 0;
    val = strtol(buffer, &endptr, 10);
    
    if (errno == ERANGE || val > INT_MAX || val < 0) {
        fprintf(stderr, "Invalid input: out of range\n");
        return EXIT_FAILURE;
    }
    
    if (endptr == buffer) {
        fprintf(stderr, "Invalid input: not a number\n");
        return EXIT_FAILURE;
    }
    
    n = (int)val;
    result = cube_sum_even(n);
    
    printf("%lld\n", result);
    
    return EXIT_SUCCESS;
}