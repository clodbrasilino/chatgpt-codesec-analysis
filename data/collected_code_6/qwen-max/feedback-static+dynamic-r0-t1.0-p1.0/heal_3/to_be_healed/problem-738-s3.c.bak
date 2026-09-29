#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double geometric_sum(int n) {
    if (n == 0) {
        return 1.0;
    }
    if (n < 0) {
        return 0.0;
    }
    return 1.0 / pow(2, n) + geometric_sum(n - 1);
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:11,src:000002,time:666,execs:290,op:havoc,rep:1; likely memory-safety defect
  */

int main() {
    int n;
    printf("Enter an integer: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }
    double result = geometric_sum(n);
    if (result == 0.0 && n < 0) {
        printf("Geometric sum is not defined for negative integers.\n");
    } else {
        printf("Geometric sum of %d is: %.10f\n", n, result);
    }
    return EXIT_SUCCESS;
}