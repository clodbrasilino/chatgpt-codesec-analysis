#include <stdio.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 28, got <no output>
  *  test case 1 failed: expected 153, got <no output>
  *  test case 2 failed: expected 496, got <no output>
  */

long long cubeSumOdd(int n) {
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        long long odd = 2LL * i + 1;
        sum += odd * odd * odd;
    }
    return sum;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:423,execs:206,op:havoc,rep:2; likely memory-safety defect
  */

int main(void) {
    int n;
    if (scanf("%d", &n) != 1 || n < 0) {
        return 1;
    }
    printf("%lld\n", cubeSumOdd(n));
    return 0;
}