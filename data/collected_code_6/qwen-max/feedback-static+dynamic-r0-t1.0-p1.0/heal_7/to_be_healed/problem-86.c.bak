#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include <inttypes.h>

int64_t centered_hexagonal_number(int64_t n) {
    if (n <= 0 || n > INT64_MAX / 3) {
        return -1;
    }
    int64_t intermediate_result = 3 * n - 3;
    if (intermediate_result > INT64_MAX - n) {
        return -1;
    }
    int64_t result = intermediate_result * n + 1;
    return result;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000004,time:844,execs:332,op:quick,pos:0; likely memory-safety defect
  */

int main() {
    int64_t n;
    printf("Enter the value of n: ");
    if (scanf("%" SCNd64, &n) != 1) {
        return 1;
    }
    int64_t result = centered_hexagonal_number(n);
    if (result == -1) {
        printf("Invalid input. The number is too large.\n");
    } else {
        printf("The %" PRId64 "th centered hexagonal number is: %" PRId64 "\n", n, result);
    }
    return 0;
}