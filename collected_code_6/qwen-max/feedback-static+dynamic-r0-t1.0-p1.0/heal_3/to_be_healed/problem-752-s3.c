#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 1, got <no output>
  *  test case 2 failed: expected 5, got <no output>
  *  test case 0 failed: expected 11, got <no output>
  */

long long jacobsthal(long n) {
    if (n <= 1) return n;
    long long a = 0, b = 1;
    for (long i = 2; i <= n; ++i) {
        long long c = a + 2 * b;
        if (c < 0 || c > LLONG_MAX) {
            fprintf(stderr, "Overflow detected\n");
            exit(EXIT_FAILURE);
        }
        a = b;
        b = c;
    }
    return b;
}

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[17];
    printf("Enter the value of n: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    char *endptr;
    long n = strtol(input, &endptr, 10);
    if (*endptr != '\n' || endptr == input) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    printf("The %ldth Jacobsthal number is: %lld\n", n, jacobsthal(n));
    return 0;
}