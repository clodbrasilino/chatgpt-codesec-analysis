#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 153, got <no output>
  *  test case 0 failed: expected 28, got <no output>
  *  test case 2 failed: expected 496, got <no output>
  */

unsigned long long cube_sum_odd(int n) {
    if (n < 0) {
        return 0;
    }
    
    if ((unsigned long long)n * 2 > ULLONG_MAX / n) {
        return 0;
    }
    
    unsigned long long n_sq = (unsigned long long)n * n;
    unsigned long long term = 2 * n_sq - 1;
    
    if (term == 0 || n_sq > ULLONG_MAX / term) {
        return 0;
    }
    
    return n_sq * term;
}

int main(int argc, char const * const argv[]) {
    int n;
    
    if (argc != 2) {
        printf("0\n");
        return 1;
    }
    
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    
    if (*endptr != '\0' || val < 0 || val > INT_MAX) {
        printf("0\n");
        return 1;
    }
    
    n = (int)val;
    unsigned long long result = cube_sum_odd(n);
    
    printf("%llu\n", result);
    
    return 0;
}