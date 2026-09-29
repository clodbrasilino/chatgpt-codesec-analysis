#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

uint64_t sum_of_fifth_powers(int n) {
    uint64_t sum = 0;
    for (int i = 1; i <= n; i++) {
        int even = 2 * i;
        sum += (uint64_t)even * even * even * even * even;
    }
    return sum;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000002,time:8471,execs:185,op:havoc,rep:3; likely memory-safety defect
  */

int main() {
    int n;
    printf("Enter the value of n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Input error\n");
        return 1;
    }
    if (n < 1) {
        fprintf(stderr, "n must be a positive integer\n");
        return 1;
    }

    uint64_t result = sum_of_fifth_powers(n);
    printf("The sum of the fifth power of the first %d even natural numbers is: %" PRIu64 "\n", n, result);
    return 0;
}