#include <stdio.h>
#include <stdlib.h>

unsigned long long sum_of_fourth_power_odd(unsigned int n) {
    unsigned long long sum = 0;
    unsigned long long odd = 1;
    unsigned int i;

    for (i = 0; i < n; ++i) {
        unsigned long long square = odd * odd;
        unsigned long long fourth = square * square;
        sum += fourth;
        odd += 2;
    }

    return sum;
}

int main(void) {
    unsigned int n;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[64];
    char *endptr;

    printf("Enter the number of odd natural numbers: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return EXIT_FAILURE;
    }

    n = (unsigned int)strtoul(input, &endptr, 10);
    if (endptr == input || *endptr != '\n') {
        fprintf(stderr, "Invalid input. Please enter a non-negative integer.\n");
        return EXIT_FAILURE;
    }

    printf("Sum of fourth powers of first %u odd natural numbers: %llu\n",
           n, sum_of_fourth_power_odd(n));

    return EXIT_SUCCESS;
}