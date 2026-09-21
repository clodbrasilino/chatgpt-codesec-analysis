#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 24, got <no output>
  *  test case 1 failed: expected 13, got <no output>
  *  test case 2 failed: expected 1, got <no output>
  */

int64_t sum_of_odd_factors(int64_t n) {
    int64_t sum = 0;
    if (n <= 0) {
        return 0;
    }
    for (int64_t i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            if (i % 2 != 0) {
                sum += i;
            }
            if ((n / i) % 2 != 0 && (n / i) != i) {
                sum += (n / i);
            }
        }
    }
    return sum;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000000,time:2149,execs:750,op:havoc,rep:10; likely memory-safety defect
  */

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Invalid input. Please enter an integer.\n");
        return EXIT_FAILURE;
    }

    char *endptr;
    int64_t number = strtoll(input, &endptr, 10);
    if (*endptr != '\n' && *endptr != '\0' || endptr == input) {
        fprintf(stderr, "Invalid input. Please enter an integer.\n");
        return EXIT_FAILURE;
    }

    int64_t result = sum_of_odd_factors(number);
    printf("Sum of odd factors: %" PRId64 "\n", result);
    return EXIT_SUCCESS;
}