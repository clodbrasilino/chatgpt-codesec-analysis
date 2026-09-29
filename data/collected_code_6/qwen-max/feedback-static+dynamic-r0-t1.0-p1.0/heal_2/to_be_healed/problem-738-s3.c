#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 1.9921875, got <no output>
  *  test case 1 failed: expected 1.9375, got <no output>
  *  test case 2 failed: expected 1.99609375, got <no output>
  */

double geometric_sum(int n) {
    if (n < 0) {
        return 0.0;
    }
    if (n == 0) {
        return 1.0;
    }
    return 1.0 / pow(2, n) + geometric_sum(n - 1);
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:11,src:000001,time:732,execs:273,op:havoc,rep:5; likely memory-safety defect
  */

int main() {
    int n;
    printf("Enter an integer: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }
    double result = geometric_sum(n);
    printf("Geometric sum of %d is: %.10f\n", n, result);
    return EXIT_SUCCESS;
}