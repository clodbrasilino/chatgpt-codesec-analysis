#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

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
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000003,time:548,execs:240,op:havoc,rep:4; likely memory-safety defect
  */

int main() {
    int64_t number;
    printf("Enter a number: ");
    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%" SCNd64, &number) != 1) {
        fprintf(stderr, "Invalid input. Please enter an integer.\n");
        return EXIT_FAILURE;
    }
    int64_t result = sum_of_odd_factors(number);
    printf("Sum of odd factors: %" PRId64 "\n", result);
    return EXIT_SUCCESS;
}