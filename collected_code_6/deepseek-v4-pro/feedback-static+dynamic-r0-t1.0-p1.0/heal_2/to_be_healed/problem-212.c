#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

unsigned long long sum_of_fourth_powers(int n) {
    if (n < 0) {
        return 0;
    }
    
    unsigned long long sum = 0;
    for (int i = 1; i <= n; i++) {
        unsigned long long fourth = (unsigned long long)i * i * i * i;
        sum += fourth;
    }
    return sum;
}

int main(void) {
    int n;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    
    printf("Enter a natural number: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    
    char *endptr;
    errno = 0;
    long value = strtol(input, &endptr, 10);
    
    if (errno == ERANGE || value > INT_MAX || value < INT_MIN) {
        fprintf(stderr, "Invalid input. Number out of range.\n");
        return 1;
    }
    
    if (endptr == input || (*endptr != '\n' && *endptr != '\0') || value < 0 || value > 1000) {
        fprintf(stderr, "Invalid input. Please enter a non-negative integer.\n");
        return 1;
    }
    
    n = (int)value;
    unsigned long long result = sum_of_fourth_powers(n);
    printf("Sum of fourth powers from 1 to %d: %llu\n", n, result);
    
    return 0;
}