#include <stdio.h>

int sum_of_squares_odd(int n) {
    int sum = 0;
    int odd = 1;
    for (int i = 0; i < n; i++) {
        sum += odd * odd;
        odd += 2;
    }
    return sum;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000002,time:253,execs:138,op:havoc,rep:2; likely memory-safety defect
  */

int main(void) {
    int n;
    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    if (n < 0) {
        printf("n must be non-negative\n");
        return 1;
    }
    printf("Sum of squares of first %d odd natural numbers: %d\n", n, sum_of_squares_odd(n));
    return 0;
}