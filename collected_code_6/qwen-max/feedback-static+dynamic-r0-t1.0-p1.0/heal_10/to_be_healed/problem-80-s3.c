#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 56.0, got <no output>
  *  test case 0 failed: expected 35.0, got <no output>
  *  test case 2 failed: expected 84.0, got <no output>
  */

long nth_tetrahedral_number(long n) {
    if (n <= 0) return 0;
    long max_div_6 = LONG_MAX / 6;
    if (n > (long)((sqrt(8.0 * (double)max_div_6 + 1.0) - 1.0) / 2.0)) {
        fprintf(stderr, "Input too large, would cause overflow.\n");
        exit(EXIT_FAILURE);
    }
    long n1 = n + 1;
    long n2 = n + 2;
    if ((n1 * n2) >= (LONG_MAX / n) || (n * (n1 * n2)) >= 6 * LONG_MAX) {
        fprintf(stderr, "Calculation would cause overflow.\n");
        exit(EXIT_FAILURE);
    }
    return (n * n1 * n2) / 6;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000000,time:769,execs:317,op:havoc,rep:6; likely memory-safety defect
  */

int main() {
    long n;
    printf("Enter the value of n: ");
    if (scanf("%ld", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        exit(EXIT_FAILURE);
    }
    long result = nth_tetrahedral_number(n);
    if (result == 0)
        printf("The %ldth tetrahedral number is: 0.0\n", n);
    else
        printf("The %ldth tetrahedral number is: %.1f\n", n, (double)result);
    return 0;
}