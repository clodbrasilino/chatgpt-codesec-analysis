#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'LLONG_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

long long cube_sum_odd_natural(int n) {
    if (n <= 0) {
        return 0;
    }
    
    long long sum = 0;
    int count = 0;
    int current = 1;
    
    while (count < n) {
        if (current % 2 != 0) {
            long long cube = (long long)current * current * current;
            /* Possible weaknesses found:
             *  'LLONG_MAX' undeclared (first use in this function)
             *  each undeclared identifier is reported only once for each function it appears in
             *  use of undeclared identifier 'LLONG_MAX'
             */
            if (sum > LLONG_MAX - cube) {
                return -1;
            }
            sum += cube;
            count++;
        }
        current++;
    }
    
    return sum;
}

int main(void) {
    int n;
    
    printf("Enter the value of n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Error: Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (n <= 0) {
        fprintf(stderr, "Error: n must be positive\n");
        return EXIT_FAILURE;
    }
    
    long long result = cube_sum_odd_natural(n);
    if (result == -1) {
        fprintf(stderr, "Error: Overflow detected\n");
        return EXIT_FAILURE;
    }
    
    printf("Sum of cubes of first %d odd natural numbers: %lld\n", n, result);
    
    return EXIT_SUCCESS;
}