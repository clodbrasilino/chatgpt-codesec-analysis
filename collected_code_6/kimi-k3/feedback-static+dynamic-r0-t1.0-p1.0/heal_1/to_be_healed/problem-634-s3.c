#include <stdio.h>

long long sumFourthPowerEven(int n) {
    long long sum = 0;
    int i;
    for (i = 1; i <= n; i++) {
        long long even = 2LL * i;
        sum += even * even * even * even;
    }
    return sum;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:314,execs:140,op:havoc,rep:2; likely memory-safety defect
  */

int main(void) {
    int n;
    long long result;
    
    if (scanf("%d", &n) != 1) {
        return 1;
    }
    
    if (n < 0) {
        return 1;
    }
    
    result = sumFourthPowerEven(n);
    printf("%lld\n", result);
    
    return 0;
}