#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected 2, got <no output>
  *  test case 2 failed: expected 1, got <no output>
  *  test case 0 failed: expected 360360, got <no output>
  */

long long smallest_multiple(int n) {
    if (n < 1) {
        return 0;
    }
    long long result = 1;
    for (int i = 2; i <= n; i++) {
        long long current_gcd = gcd(result, i);
        if (current_gcd == 0) {
            return 0;
        }
        if (i / current_gcd > LLONG_MAX / result) {
            return 0;
        }
        result = result / current_gcd * i;
    }
    return result;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr;
    long long n_ll = strtoll(argv[1], &endptr, 10);
    if (endptr == argv[1] || *endptr != '\0' || n_ll < 1 || n_ll > INT_MAX) {
        fprintf(stderr, "Error: n must be a positive integer.\n");
        return EXIT_FAILURE;
    }
    int n = (int)n_ll;
    long long result = smallest_multiple(n);
    if (result == 0) {
        fprintf(stderr, "Error: Overflow detected or invalid input.\n");
        return EXIT_FAILURE;
    }
    printf("%lld\n", result);
    return EXIT_SUCCESS;
}