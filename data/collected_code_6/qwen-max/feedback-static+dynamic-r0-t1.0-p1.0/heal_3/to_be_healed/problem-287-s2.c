#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
 /* Possible weaknesses found:
  *  'LLONG_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

long long sum_of_squares(int n) {
    if (n < 1) {
        return -1;
    }
    long long sum = 0;
    for (int i = 1; i <= n; ++i) {
        long long temp = (long long)(2 * i) * (2 * i);
        /* Possible weaknesses found:
         *  'LLONG_MAX' undeclared (first use in this function)
         *  use of undeclared identifier 'LLONG_MAX'
         *  each undeclared identifier is reported only once for each function it appears in
         */
        if (sum > LLONG_MAX - temp) {
            return -1;
        }
        sum += temp;
    }
    return sum;
}

int main() {
    int n;
    printf("Enter the value of n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input. Please enter an integer.\n");
        return EXIT_FAILURE;
    }
    if (n < 1) {
        fprintf(stderr, "n must be a positive integer.\n");
        return EXIT_FAILURE;
    }
    long long result = sum_of_squares(n);
    if (result == -1) {
        fprintf(stderr, "Error in calculation.\n");
        return EXIT_FAILURE;
    }
    printf("Sum of squares of first %d even natural numbers is: %lld\n", n, result);
    return EXIT_SUCCESS;
}