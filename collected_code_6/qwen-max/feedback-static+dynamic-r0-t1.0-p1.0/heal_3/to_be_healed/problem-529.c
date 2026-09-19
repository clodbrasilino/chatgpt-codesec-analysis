#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 31, got 53
  *  test case 2 failed: expected 17, got 22
  *  test case 1 failed: expected 5, got 4
  */

long long jacobsthal_lucas(long n) {
    if (n == 0) return 2;
    if (n == 1) return 1;

    int64_t a = 2, b = 1;
    for (long i = 2; i <= n; i++) {
        int64_t c = a + 2 * b;
        a = b;
        b = c;
    }
    return b;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:101,execs:126,op:havoc,rep:2; likely memory-safety defect
  */

int main() {
    long n;
    printf("Enter the value of n: ");
    if (scanf("%ld", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    int64_t result = jacobsthal_lucas(n);
    printf("The %ldth Jacobsthal-Lucas number is: %" PRId64 "\n", n, result);
    return EXIT_SUCCESS;
}