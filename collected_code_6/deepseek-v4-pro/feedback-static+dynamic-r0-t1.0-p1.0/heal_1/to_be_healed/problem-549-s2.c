#include <stdio.h>

long long sum_fifth_power_odd(int n) {
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        long long odd = 2LL * i + 1;
        sum += odd * odd * odd * odd * odd;
    }
    return sum;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000000,time:81,execs:54,op:havoc,rep:3; likely memory-safety defect
  */

int main(void) {
    int n;
    printf("Enter n: ");
    if (scanf("%d", &n) != 1 || n < 0) {
        printf("Invalid input\n");
        return 1;
    }
    printf("Sum = %lld\n", sum_fifth_power_odd(n));
    return 0;
}