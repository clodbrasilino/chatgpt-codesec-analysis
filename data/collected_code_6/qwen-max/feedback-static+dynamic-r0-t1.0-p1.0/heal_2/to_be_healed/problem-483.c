#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

unsigned long long factorial(unsigned int n) {
    unsigned long long result = 1;
    for (unsigned int i = 2; i <= n; ++i) {
        if (ULLONG_MAX / i < result) {
            return 0; // Handle overflow
        }
        result *= i;
    }
    return result;
}

unsigned int find_number_divisible_by_x(unsigned int x) {
    unsigned int i = 1;
    while (1) {
        unsigned long long fact = factorial(i);
        /* Possible weaknesses found:
         *  Assuming that condition 'fact==0' is not redundant
         */
        if (fact == 0 || fact % x == 0) {
            return i;
        }
        i++;
        /* Possible weaknesses found:
         *  Condition 'fact==0' is always false
         *  Condition 'fact==0' is always false [knownConditionTrueFalse]
         */
        if (fact == 0) break; // Stop if overflow is detected
    }
    return 0; // Return 0 if no such number is found
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000004,time:573,execs:256,op:havoc,rep:2; likely memory-safety defect
  */

int main() {
    unsigned int x;
    printf("Enter a number: ");
    if (scanf("%u", &x) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    unsigned int result = find_number_divisible_by_x(x);
    if (result != 0) {
        printf("The first natural number whose factorial is divisible by %u is: %u\n", x, result);
    } else {
        printf("No natural number found whose factorial is divisible by %u\n", x);
    }
    return EXIT_SUCCESS;
}