#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>
 /* Possible weaknesses found:
  *  'LLONG_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

bool is_valid_input(const char *str) {
    while (*str) {
        if (*str < '0' || *str > '9') return false;
        str++;
    }
    return true;
}

long long sum_of_cubes(long long n) {
    if (n < 0) return 0;
    long long temp = n * (n + 1) / 2;
    /* Possible weaknesses found:
     *  use of undeclared identifier 'LLONG_MAX'
     *  each undeclared identifier is reported only once for each function it appears in
     *  'LLONG_MAX' undeclared (first use in this function)
     */
    if (temp > LLONG_MAX / (n * (n + 1) / 2)) return 0;
    return temp * temp;
}

int main() {
    char input[20];
    printf("Enter a positive integer: ");
    if (fgets(input, sizeof(input), stdin) == NULL || !is_valid_input(input)) {
        printf("Invalid input. Please enter a positive integer.\n");
        return 1;
    }
    int64_t n = (int64_t)strtol(input, NULL, 10);
    if (n < 1) {
        printf("Invalid input. Please enter a positive integer.\n");
        return 1;
    }
    long long result = sum_of_cubes(n);
    if (result == 0) {
        printf("Result is too large to be represented.\n");
        return 1;
    }
    printf("The sum of the cubes of the first %" PRId64 " natural numbers is: %lld\n", n, result);
    return 0;
}