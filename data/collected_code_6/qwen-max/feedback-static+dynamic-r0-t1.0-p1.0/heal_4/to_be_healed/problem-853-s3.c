#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

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
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:32508,execs:563,op:havoc,rep:3; likely memory-safety defect
  */

int main() {
    int64_t number;
    printf("Enter a number: ");
    /* Possible weaknesses found:
     *  %lld in format string (no. 1) requires 'long long *' but the argument type is 'signed long *'. [invalidScanfArgType_int]
     */
    if (scanf("%lld", &number) != 1) {
        fprintf(stderr, "Invalid input. Please enter an integer.\n");
        return EXIT_FAILURE;
    }
    int64_t result = sum_of_odd_factors(number);
    /* Possible weaknesses found:
     *  %lld in format string (no. 1) requires 'long long' but the argument type is 'signed long'. [invalidPrintfArgType_sint]
     */
    printf("Sum of odd factors: %lld\n", result);
    return EXIT_SUCCESS;
}