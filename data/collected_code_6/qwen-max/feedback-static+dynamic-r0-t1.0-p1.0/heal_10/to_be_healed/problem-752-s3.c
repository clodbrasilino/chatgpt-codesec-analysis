#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <errno.h>
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
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000002,time:3253,execs:1077,op:havoc,rep:4; likely memory-safety defect
  */

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[20];
    printf("Enter the value of n: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    input[strcspn(input, "\n")] = 0;
    errno = 0;
    long n = strtol(input, NULL, 10);
    if (errno == ERANGE || n > LONG_MAX || n < 0) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    if (n > 63) {
        fprintf(stderr, "Input value too large\n");
        return 1;
    }
    printf("The %ldth Jacobsthal number is: %lld\n", n, jacobsthal(n));
    return 0;
}