#include <stdio.h>

double average_of_cubes(int n) {
    if (n <= 0) {
        return 0.0;
    }
    long long sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += (long long)i * i * i;
    }
    return (double)sum / n;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000003,time:296,execs:175,op:havoc,rep:4; likely memory-safety defect
  */

int main(void) {
    int n;
    printf("Enter a positive integer: ");
    if (scanf("%d", &n) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    if (n <= 0) {
        printf("Please enter a positive integer\n");
        return 1;
    }
    printf("Average of cubes of first %d natural numbers: %.2f\n", n, average_of_cubes(n));
    return 0;
}