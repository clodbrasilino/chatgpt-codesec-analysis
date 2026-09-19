#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 12, got <no output>
  *  test case 2 failed: expected 1, got <no output>
  *  test case 0 failed: expected 4.5, got <no output>
  */

double average_of_cubes(int n) {
    if (n <= 0) return 0.0;

    long sum = 0;
    for (int i = 1; i <= n; ++i) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 9223193340756366400 + 473384830201856 cannot be represented in type 'long' (AFL crash: id:000000,sig:06,src:000001,time:510,execs:212,op:havoc,rep:2)
         */
        sum += (long)i * i * i;
    }
    return (double)sum / n;
}

int main() {
    int n;
    printf("Enter the value of n: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    double result = average_of_cubes(n);
    printf("The average of cubes of first %d natural numbers is: %.2f\n", n, result);

    return EXIT_SUCCESS;
}