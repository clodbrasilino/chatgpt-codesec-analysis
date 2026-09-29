#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int64_t sum_of_fourth_powers(int n) {
    int64_t sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += (2 * (int64_t)i) * (2 * (int64_t)i) * (2 * (int64_t)i) * (2 * (int64_t)i);
    }
    return sum;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:461,execs:203,op:havoc,rep:2; likely memory-safety defect
  */

int main() {
    int n;
    printf("Enter the value of n: ");
    if (scanf("%d", &n) != 1 || n < 1) {
        fprintf(stderr, "Invalid input. Please enter a positive integer.\n");
        return EXIT_FAILURE;
    }
    int64_t result = sum_of_fourth_powers(n);
    printf("The sum of the fourth powers of the first %d even natural numbers is: %ld\n", n, result);
    return EXIT_SUCCESS;
}