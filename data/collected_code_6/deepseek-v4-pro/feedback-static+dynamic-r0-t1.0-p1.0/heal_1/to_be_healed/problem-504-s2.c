#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

unsigned long long cube_sum_natural_numbers(int n) {
    if (n < 0) {
        return 0;
    }
    
    unsigned long long sum = 0;
    unsigned long long nn = (unsigned long long)n;
    
    sum = (nn * nn * (nn + 1) * (nn + 1)) / 4;
    
    return sum;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[32];
    char *endptr;
    long n;
    
    printf("Enter a positive integer: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    errno = 0;
    n = strtol(input, &endptr, 10);
    
    if (errno == ERANGE || n < 0 || n > INT_MAX) {
        fprintf(stderr, "Input out of range\n");
        return EXIT_FAILURE;
    }
    
    if (endptr == input || *endptr != '\n') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    unsigned long long result = cube_sum_natural_numbers((int)n);
    printf("Cube sum of first %d natural numbers: %llu\n", (int)n, result);
    
    return EXIT_SUCCESS;
}