#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int last_two_digits_factorial(int n) {
    if (n < 0) {
        return -1;
    }
    if (n >= 10) {
        return 0;
    }
    
    int result = 1;
    for (int i = 2; i <= n; i++) {
        result = (result * i) % 100;
    }
    return result;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[128];
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    errno = 0;
    char *endptr;
    long val = strtol(buffer, &endptr, 10);
    
    if (endptr == buffer) {
        fprintf(stderr, "Invalid input format\n");
        return EXIT_FAILURE;
    }
    
    if (errno == ERANGE || val > INT_MAX || val < INT_MIN) {
        fprintf(stderr, "Input out of range\n");
        return EXIT_FAILURE;
    }
    
    while (*endptr == ' ' || *endptr == '\t' || *endptr == '\n' || *endptr == '\r') {
        endptr++;
    }
    
    if (*endptr != '\0') {
        fprintf(stderr, "Invalid input format\n");
        return EXIT_FAILURE;
    }
    
    int n = (int)val;
    
    if (n < 0) {
        fprintf(stderr, "Input must be non-negative\n");
        return EXIT_FAILURE;
    }
    
    int result = last_two_digits_factorial(n);
    printf("%02d\n", result);
    
    return EXIT_SUCCESS;
}