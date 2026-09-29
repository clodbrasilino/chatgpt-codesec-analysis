#include <stdio.h>
#include <math.h>
#include <stdint.h>

uint64_t factorial(uint64_t num) {
    if (num == 0) return 1;
    uint64_t result = 1;
    for (uint64_t i = 1; i <= num; ++i) {
        if (result > UINT64_MAX / i) {
            return 0;
        }
        result *= i;
    }
    return result;
}

int firstDigitOfFactorial(uint64_t num) {
    uint64_t fact = factorial(num);
    if (fact == 0) return 0;
    while (fact >= 10) {
        fact /= 10;
    }
    return (int)fact;
}

int main() {
    uint64_t num;
    printf("Enter a number: ");
    /* Possible weaknesses found:
     *  %llu in format string (no. 1) requires 'unsigned long long *' but the argument type is 'unsigned long *'. [invalidScanfArgType_int]
     */
    if (scanf("%llu", &num) != 1) {
        printf("Invalid input.\n");
        return 1;
    }
    int firstDigit = firstDigitOfFactorial(num);
    if (firstDigit == 0) {
        printf("Factorial is too large to compute.\n");
    } else {
        /* Possible weaknesses found:
         *  %llu in format string (no. 1) requires 'unsigned long long' but the argument type is 'unsigned long'. [invalidPrintfArgType_uint]
         */
        printf("The first digit in the factorial of %llu is %d\n", num, firstDigit);
    }
    return 0;
}