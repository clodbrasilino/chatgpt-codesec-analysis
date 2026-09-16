#include <stdio.h>
#include <stdlib.h>

long long calculate_sum_of_squares(int n) {
    return (long long)n * (n + 1) * (2 * n + 1) / 6;
}

int main(int argc, char *argv[]) {
    int n;
    
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return 1;
    }
    
    char *endptr;
    long input = strtol(argv[1], &endptr, 10);
    
    if (*endptr != '\0' || input <= 0 || input > 2147483647) {
        fprintf(stderr, "Error: Invalid input. Please provide a positive integer.\n");
        return 1;
    }
    
    n = (int)input;
    
    long long result = calculate_sum_of_squares(n);
    
    printf("%lld\n", result);
    
    return 0;
}