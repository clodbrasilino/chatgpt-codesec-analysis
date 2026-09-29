#include <stdio.h>

long long cube_sum_natural(int n) {
    long long sum = 0;
    for (int i = 1; i <= n; i++) {
        long long cube = (long long)i * i * i;
        sum += cube;
    }
    return sum;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000003,time:449,execs:251,op:havoc,rep:3; likely memory-safety defect
  */

int main(void) {
    int n;
    printf("Enter a positive integer: ");
    if (scanf("%d", &n) != 1 || n < 0) {
        printf("Invalid input.\n");
        return 1;
    }
    printf("Cube sum of first %d natural numbers: %lld\n", n, cube_sum_natural(n));
    return 0;
}