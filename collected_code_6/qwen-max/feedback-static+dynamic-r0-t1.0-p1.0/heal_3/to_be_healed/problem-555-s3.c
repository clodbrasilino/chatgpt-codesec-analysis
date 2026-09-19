#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
 /* Possible weaknesses found:
  *  'LLONG_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

long long sum_of_cubes(long n) {
    /* Possible weaknesses found:
     *  use of undeclared identifier 'LLONG_MAX'
     *  each undeclared identifier is reported only once for each function it appears in
     *  'LLONG_MAX' undeclared (first use in this function)
     */
    if (n > 0 && n * n > LLONG_MAX / n) return 0;
    long long result = (n * (n + 1) / 2);
    /* Possible weaknesses found:
     *  use of undeclared identifier 'LLONG_MAX'
     */
    if (result * result > LLONG_MAX) return 0;
    return result * result;
}

long long sum_of_numbers(long n) {
    /* Possible weaknesses found:
     *  use of undeclared identifier 'LLONG_MAX'
     *  'LLONG_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
     *  'LLONG_MAX' undeclared (first use in this function)
     */
    if (n > 0 && n + 1 > LLONG_MAX / n) return 0;
    return (n * (n + 1)) / 2;
}

long long difference(long n) {
    long long cubes = sum_of_cubes(n);
    long long numbers = sum_of_numbers(n);
    if (cubes < 0 || numbers < 0) return 0;
    return cubes - numbers;
}

int main() {
    long n;
    printf("Enter a natural number: ");
    if (scanf("%ld", &n) != 1 || n < 1) {
        printf("Please enter a valid natural number.\n");
        return 1;
    }

    long long diff = difference(n);
    printf("The difference is: %lld\n", diff);
    return 0;
}