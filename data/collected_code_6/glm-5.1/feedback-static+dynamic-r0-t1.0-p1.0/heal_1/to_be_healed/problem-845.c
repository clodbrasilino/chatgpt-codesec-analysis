#include <stdio.h>
#include <math.h>

int count_factorial_digits(int n) {
    if (n < 0) {
        return -1;
    }
    if (n <= 1) {
        return 1;
    }
    double log_sum = 0.0;
    for (int i = 2; i <= n; i++) {
        log_sum += log10((double)i);
    }
    return (int)floor(log_sum) + 1;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:4887,execs:261,op:havoc,rep:1; likely memory-safety defect
  */

int main() {
    int n;
    if (scanf("%d", &n) != 1) {
        return 1;
    }
    int result = count_factorial_digits(n);
    if (result == -1) {
        return 1;
    }
    printf("%d\n", result);
    return 0;
}