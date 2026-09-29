#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include <inttypes.h>

int64_t nth_centered_hexagonal(int64_t n) {
    if (n > 0x1FFFFFFFFFFFFFFFLL || n < -0x1FFFFFFFFFFFFFFFLL) {
        fprintf(stderr, "Input out of range\n");
        return -1;
    }
    int64_t max_n = LLONG_MAX / 3 / (n - 1);
    if (n > max_n || n < -max_n) {
        fprintf(stderr, "Overflow detected\n");
        return -1;
    }
    int64_t result = 3 * n * (n - 1) + 1;
    if (result < 0) {
        fprintf(stderr, "Result overflow\n");
        return -1;
    }
    return result;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000002,time:275,execs:156,op:havoc,rep:6; likely memory-safety defect
  */

int main() {
    int64_t n;
    printf("Enter the value of n: ");
    if (scanf("%" SCNd64, &n) != 1) {
        fprintf(stderr, "Input error\n");
        return 1;
    }
    int64_t result = nth_centered_hexagonal(n);
    if (result == -1) {
        return 1;
    }
    printf("The %" PRId64 "th centered hexagonal number is: %" PRId64 "\n", n, result);
    return 0;
}