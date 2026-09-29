#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

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
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[20];
    /* Possible weaknesses found:
     * Flawfinder sscanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (fgets(input, sizeof(input), stdin) != NULL && sscanf(input, "%" SCNu64, &num) == 1) {
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
    return 0;
}