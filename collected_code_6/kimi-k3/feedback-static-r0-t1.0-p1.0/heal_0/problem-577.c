#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int get_last_digit_factorial(int n) {
    if (n < 0) {
        return -1;
    }
    if (n >= 5) {
        return 0;
    }
    
    int result = 1;
    for (int i = 2; i <= n; i++) {
        result = (result * i) % 10;
    }
    return result;
}

int main(void) {
    char input[32];
    char *endptr;
    long num;
    
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    errno = 0;
    num = strtol(input, &endptr, 10);
    
    if (errno == ERANGE || num > INT_MAX || num < INT_MIN) {
        fprintf(stderr, "Number out of range\n");
        return EXIT_FAILURE;
    }
    
    if (endptr == input || (*endptr != '\n' && *endptr != '\0')) {
        fprintf(stderr, "Invalid input format\n");
        return EXIT_FAILURE;
    }
    
    int n = (int)num;
    int last_digit = get_last_digit_factorial(n);
    
    if (last_digit == -1) {
        fprintf(stderr, "Factorial not defined for negative numbers\n");
        return EXIT_FAILURE;
    }
    
    printf("%d\n", last_digit);
    return EXIT_SUCCESS;
}