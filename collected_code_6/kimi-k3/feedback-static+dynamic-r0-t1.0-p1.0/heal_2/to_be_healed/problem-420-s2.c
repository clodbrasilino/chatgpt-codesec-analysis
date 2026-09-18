#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

int64_t cubeSumEvenNatural(int n) {
    int64_t sum = 0;
    for (int i = 1; i <= n; i++) {
        int64_t even = 2LL * i;
        if (even > 2097152) {
            return -1;
        }
        int64_t cube = even * even * even;
        if (sum > INT64_MAX - cube) {
            return -1;
        }
        sum += cube;
    }
    return sum;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000000,time:439,execs:197,op:havoc,rep:4; likely memory-safety defect
  */

int main(void) {
    int n;
    if (scanf("%d", &n) != 1 || n < 0) {
        return 1;
    }
    printf("%" PRId64 "\n", cubeSumEvenNatural(n));
    return 0;
}