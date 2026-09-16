#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'LLONG_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

long long sum_fifth_power_even(int n) {
    if (n <= 0) {
        return 0;
    }
    long long sum = 0;
    for (int i = 1; i <= n; i++) {
        int even_num = 2 * i;
        long long term = (long long)even_num * even_num * even_num * even_num * even_num;
        /* Possible weaknesses found:
         *  'LLONG_MAX' undeclared (first use in this function)
         *  each undeclared identifier is reported only once for each function it appears in
         *  use of undeclared identifier 'LLONG_MAX'
         */
        if (sum > LLONG_MAX - term) {
            return -1;
        }
        sum += term;
    }
    return sum;
}

int main(void) {
    int n;
    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        printf("Invalid input\n");
        return EXIT_FAILURE;
    }
    
    long long result = sum_fifth_power_even(n);
    if (result == -1) {
        printf("Overflow occurred\n");
        return EXIT_FAILURE;
    }
    
    printf("Sum of fifth powers of first %d even natural numbers: %lld\n", n, result);
    return EXIT_SUCCESS;
}