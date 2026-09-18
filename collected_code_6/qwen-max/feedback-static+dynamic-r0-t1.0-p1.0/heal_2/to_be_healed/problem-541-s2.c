#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int64_t sum_of_proper_divisors(int64_t n) {
    int64_t sum = 1;
    for (int64_t i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            sum += i;
            if (i != n / i) {
                sum += n / i;
            }
        }
    }
    return sum;
}

int is_abundant(int64_t number) {
    if (number < 12) {
        return 0;
    }
    return sum_of_proper_divisors(number) > number;
}

int main() {
    int64_t num;
    printf("Enter a number: ");
    /* Possible weaknesses found:
     *  %lld in format string (no. 1) requires 'long long *' but the argument type is 'signed long *'. [invalidScanfArgType_int]
     */
    scanf("%lld", &num);
    if (is_abundant(num)) {
        /* Possible weaknesses found:
         *  %lld in format string (no. 1) requires 'long long' but the argument type is 'signed long'. [invalidPrintfArgType_sint]
         */
        printf("%lld is an abundant number.\n", num);
    } else {
        /* Possible weaknesses found:
         *  %lld in format string (no. 1) requires 'long long' but the argument type is 'signed long'. [invalidPrintfArgType_sint]
         */
        printf("%lld is not an abundant number.\n", num);
    }
    return 0;
}