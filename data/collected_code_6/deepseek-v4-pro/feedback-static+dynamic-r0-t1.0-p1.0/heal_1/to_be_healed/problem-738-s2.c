#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 1.99609375, got 1.9921875
  *  test case 0 failed: expected 1.9921875, got 1.984375
  *  test case 1 failed: expected 1.9375, got 1.875
  */

double geometric_sum(int n) {
    if (n < 1) {
        return 0.0;
    }
    if (n == 1) {
        return 1.0;
    }
    return 1.0 + geometric_sum(n - 1) / 2.0;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:11,src:000004,time:781,execs:458,op:havoc,rep:1; likely memory-safety defect
  */

int main(void) {
    int n;
    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    if (n < 1) {
        fprintf(stderr, "n must be at least 1\n");
        return EXIT_FAILURE;
    }
    printf("Geometric sum: %.10f\n", geometric_sum(n));
    return EXIT_SUCCESS;
}