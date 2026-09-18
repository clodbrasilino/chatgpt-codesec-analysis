#include <stdio.h>

double harmonic_sum(int n) {
    if (n <= 1) return 1.0;
    return 1.0 / n + harmonic_sum(n - 1);
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:11,src:000001,time:378,execs:133,op:havoc,rep:3; likely memory-safety defect
  */

int main() {
    int n;
    printf("Enter a positive integer: ");
    scanf("%d", &n);

    if (n > 0) {
        double result = harmonic_sum(n);
        printf("Harmonic sum of %d-1 is: %f\n", n, result);
    } else {
        printf("Please enter a positive integer.\n");
    }

    return 0;
}