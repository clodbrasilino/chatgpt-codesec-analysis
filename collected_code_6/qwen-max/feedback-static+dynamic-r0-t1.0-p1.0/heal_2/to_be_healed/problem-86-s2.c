#include <stdio.h>
#include <stdint.h>

int64_t nth_centered_hexagonal(int64_t n) {
    if (n > 0x1FFFFFFFFFFFFFFF || n < -0x1FFFFFFFFFFFFFFF) {
        fprintf(stderr, "Input out of range\n");
        return -1;
    }
    int64_t result = 3 * n * (n - 1) + 1;
    if (result / n != 3 * (n - 1) + 1) {
        fprintf(stderr, "Overflow detected\n");
        return -1;
    }
    return result;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000002,time:620,execs:296,op:havoc,rep:3; likely memory-safety defect
  */

int main() {
    int64_t n;
    printf("Enter the value of n: ");
    if (scanf("%ld", &n) != 1) {
        fprintf(stderr, "Input error\n");
        return 1;
    }
    int64_t result = nth_centered_hexagonal(n);
    if (result == -1) {
        return 1;
    }
    printf("The %ldth centered hexagonal number is: %ld\n", n, result);
    return 0;
}