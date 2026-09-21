#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>

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
    char input[20];
    if (fgets(input, sizeof(input), stdin) != NULL) {
        char *endptr;
        uint64_t num = strtoull(input, &endptr, 10);
        if (*endptr == '\n' || *endptr == '\0') {
            int firstDigit = firstDigitOfFactorial(num);
            if (firstDigit == 0) {
                printf("Factorial is too large to compute.\n");
            } else {
                printf("The first digit in the factorial of %" PRIu64 " is %d\n", num, firstDigit);
            }
        } else {
            printf("Invalid input.\n");
            return 1;
        }
    } else {
        printf("Invalid input.\n");
        return 1;
    }
    return 0;
}