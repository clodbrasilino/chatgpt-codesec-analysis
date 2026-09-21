#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 1, got 2
  *  test case 2 failed: expected 5, got 12
  *  test case 0 failed: expected 11, got 29
  */

long long jacobsthal(long n) {
    if (n <= 1) return n;
    long long a = 0, b = 1;
    for (long i = 2; i <= n; ++i) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 4866752642924153522 + 5052016396815640554 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000004,time:46729,execs:40038,op:havoc,rep:3)
         * UBSan: signed integer overflow: 2 * 4866752642924153522 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000004,time:46729,execs:40038,op:havoc,rep:3)
         */
        long long c = a + 2 * b;
        a = b;
        b = c;
    }
    return b;
}

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[16];
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