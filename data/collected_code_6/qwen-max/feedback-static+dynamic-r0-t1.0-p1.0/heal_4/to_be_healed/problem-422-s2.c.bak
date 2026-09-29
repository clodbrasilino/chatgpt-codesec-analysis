#include <stdio.h>
#include <stdlib.h>

double average_of_cubes(int n) {
    if (n <= 0) return 0.0;

    long long sum = 0;
    for (int i = 1; i <= n; ++i) {
        sum += (long long)i * i * i;
    }
    return (double)sum / n;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000002,time:937,execs:435,op:havoc,rep:1; likely memory-safety defect
  */

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