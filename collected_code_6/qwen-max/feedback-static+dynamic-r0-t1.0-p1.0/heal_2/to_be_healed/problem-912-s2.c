#include <stdio.h>
#include <stdlib.h>

long long ln_m_lobb(long n) {
    if (n <= 1) return 0;
    long long a = 2, b = 4, c = 0;
    for (long i = 3; i <= n; ++i) {
        c = a + b;
        a = b;
        b = c;
    }
    return c % 1000000007;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000000,time:690,execs:722,op:havoc,rep:3; likely memory-safety defect
  */

int main() {
    long n;
    printf("Enter the value of n: ");
    if (scanf("%ld", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    long long result = ln_m_lobb(n);
    printf("The Lobb number is: %lld\n", result);
    return EXIT_SUCCESS;
}