#include <stdio.h>

long long cubeSumOdd(int n) {
    long long sum = 0;
    for (int i = 1; i <= n; i++) {
        long long odd = 2LL * i - 1;
        sum += odd * odd * odd;
    }
    return sum;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000000,time:247,execs:124,op:havoc,rep:9; likely memory-safety defect
  */

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) {
        return 1;
    }
    printf("%lld\n", cubeSumOdd(n));
    return 0;
}