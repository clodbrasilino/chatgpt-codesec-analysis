#include <stdio.h>
#include <stdlib.h>

unsigned long long int sumOfSquaresOfOddNumbers(unsigned int n) {
    if (n == 0) {
        return 0;
    }

    unsigned long long int sum = 0;
    unsigned long long int currentOdd = 1;

    for (unsigned int i = 0; i < n; i++) {
        sum += currentOdd * currentOdd;
        currentOdd += 2;
    }

    return sum;
}

int main(void) {
    unsigned int n = 0;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[128];

    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        if (sscanf(buffer, "%u", &n) != 1) {
            fprintf(stderr, "Invalid input\n");
            return EXIT_FAILURE;
        }

        unsigned long long int result = sumOfSquaresOfOddNumbers(n);
        printf("%llu\n", result);
    } else {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}