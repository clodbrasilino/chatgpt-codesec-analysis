#include <stdio.h>

void calculateSumAndAverage(int n, int *sum, float *average) {
    *sum = 0;
    for (int i = 1; i <= n; i++) {
        *sum += i;
    }
    if (n > 0) {
        *average = (float)*sum / n;
    } else {
        *average = 0.0f;
    }
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000000,time:3463,execs:1392,op:havoc,rep:5; likely memory-safety defect
  */

int main() {
    int n;
    printf("Enter the value of n: ");
    scanf("%d", &n);

    int sum;
    float average;
    calculateSumAndAverage(n, &sum, &average);

    printf("Sum of first %d natural numbers is %d\n", n, sum);
    printf("Average of first %d natural numbers is %.2f\n", n, average);

    return 0;
}