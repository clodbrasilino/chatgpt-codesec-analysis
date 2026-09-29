#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long cube_sum_of_even(int n) {
    if (n < 0 || n > INT_MAX / 2) {
        return -1;
    }
    long long sum = 0;
    for (int i = 1; i <= n; ++i) {
        long long even = 2 * (long long)i;
        sum += even * even * even;
    }
    return sum;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:949,execs:379,op:havoc,rep:15; likely memory-safety defect
  */

int main() {
    int n;
    printf("Enter the number of first even natural numbers: ");
    if (scanf("%d", &n) != 1 || n < 0) {
        fprintf(stderr, "Invalid input. Please enter a non-negative integer.\n");
        return EXIT_FAILURE;
    }
    long long result = cube_sum_of_even(n);
    if (result == -1) {
        fprintf(stderr, "Input out of range. Please enter a smaller non-negative integer.\n");
        return EXIT_FAILURE;
    }
    printf("The cube sum of the first %d even natural numbers is: %lld\n", n, result);
    return EXIT_SUCCESS;
}