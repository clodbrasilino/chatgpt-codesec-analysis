#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

uint64_t cube_sum_of_evens(int n) {
    uint64_t sum = 0;
    for (int i = 1; i <= n; ++i) {
        int64_t even_number = 2 * i;
        sum += (uint64_t)even_number * even_number * even_number;
    }
    return sum;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:6070,execs:1927,op:havoc,rep:3; likely memory-safety defect
  */

int main() {
    int n;
    if (scanf("%d", &n) != 1 || n < 1) {
        fprintf(stderr, "Invalid input. Please enter a positive integer.\n");
        return EXIT_FAILURE;
    }
    uint64_t result = cube_sum_of_evens(n);
    printf("The cube sum of the first %d even natural numbers is: %" PRIu64 "\n", n, result);
    return EXIT_SUCCESS;
}