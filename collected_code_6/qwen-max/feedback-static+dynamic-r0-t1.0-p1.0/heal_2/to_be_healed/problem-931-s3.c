#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
 /* Possible weaknesses found:
  *  'LLONG_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

bool is_safe_to_add(long long a, long long b) {
    /* Possible weaknesses found:
     *  'LLONG_MAX' undeclared (first use in this function)
     *  use of undeclared identifier 'LLONG_MAX'
     *  each undeclared identifier is reported only once for each function it appears in
     */
    if (a > 0 && b > 0 && a > LLONG_MAX - b) return false;
    /* Possible weaknesses found:
     *  'LLONG_MIN' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
     *  'LLONG_MIN' undeclared (first use in this function)
     *  use of undeclared identifier 'LLONG_MIN'
     */
    if (a < 0 && b < 0 && a < LLONG_MIN - b) return false;
    return true;
}

long long sum_of_cubes(int n) {
    long long sum = 0;
    for (int i = 1; i <= n; ++i) {
        long long cube = (long long)i * i * i;
        if (!is_safe_to_add(sum, cube)) {
            printf("Overflow detected. Result is not representable.\n");
            return -1;
        }
        sum += cube;
    }
    return sum;
}

int main() {
    int n;
    printf("Enter a positive integer: ");
    if (scanf("%d", &n) != 1 || n < 1) {
        printf("Invalid input. Please enter a positive integer.\n");
        return 1;
    }
    long long result = sum_of_cubes(n);
    if (result == -1) {
        return 1;
    }
    printf("The sum of cubes up to %d is: %lld\n", n, result);
    return 0;
}