#include <stdio.h>
#include <stdlib.h>

long long cube_sum_of_even(int n) {
    long long sum = 0;
    for (int i = 1; i <= n; ++i) {
        int even = 2 * i;
        sum += (long long)even * even * even;
    }
    return sum;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000002,time:299,execs:155,op:havoc,rep:3; likely memory-safety defect
  */

int main() {
    int n;
    printf("Enter the number of first even natural numbers: ");
    if (scanf("%d", &n) != 1 || n < 0) {
        fprintf(stderr, "Invalid input. Please enter a non-negative integer.\n");
        return EXIT_FAILURE;
    }
    long long result = cube_sum_of_even(n);
    printf("The cube sum of the first %d even natural numbers is: %lld\n", n, result);
    return EXIT_SUCCESS;
}