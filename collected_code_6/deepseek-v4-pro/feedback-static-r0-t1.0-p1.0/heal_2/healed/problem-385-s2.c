#include <stdio.h>
#include <stdlib.h>

int perrin_recursive(int n) {
    if (n == 0) return 3;
    if (n == 1) return 0;
    if (n == 2) return 2;
    return perrin_recursive(n - 2) + perrin_recursive(n - 3);
}

int main(int argc, const char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return 1;
    }
    
    char *endptr;
    long n = strtol(argv[1], &endptr, 10);
    
    if (*endptr != '\0' || n < 0) {
        fprintf(stderr, "Error: Invalid input. Please provide a non-negative integer.\n");
        return 1;
    }
    
    if (n > 30) {
        fprintf(stderr, "Error: Input too large. Maximum supported value is 30.\n");
        return 1;
    }
    
    printf("%d\n", perrin_recursive((int)n));
    return 0;
}