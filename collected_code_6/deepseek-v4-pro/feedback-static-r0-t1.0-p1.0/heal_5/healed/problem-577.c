#include <stdio.h>
#include <stdlib.h>

int last_digit_factorial(int n) {
    if (n < 0) {
        return -1;
    }
    if (n == 0 || n == 1) {
        return 1;
    }
    if (n >= 5) {
        return 0;
    }
    
    int factorial = 1;
    for (int i = 2; i <= n; i++) {
        factorial *= i;
    }
    return factorial % 10;
}

int main(int argc, const char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <integer>\n", argv[0]);
        return 1;
    }
    
    char *endptr;
    long num = strtol(argv[1], &endptr, 10);
    
    if (*endptr != '\0' || endptr == argv[1]) {
        fprintf(stderr, "Error: Invalid integer input\n");
        return 1;
    }
    
    if (num < 0 || num > 2147483647) {
        fprintf(stderr, "Error: Input out of valid range (0-2147483647)\n");
        return 1;
    }
    
    int result = last_digit_factorial((int)num);
    
    if (result == -1) {
        fprintf(stderr, "Error: Invalid input\n");
        return 1;
    }
    
    printf("%d\n", result);
    return 0;
}