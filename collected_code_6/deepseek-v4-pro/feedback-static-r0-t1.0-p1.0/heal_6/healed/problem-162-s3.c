#include <stdio.h>
#include <stdlib.h>

int sum_positive_integers(int n) {
    if (n <= 0) {
        return 0;
    }
    
    int sum = 0;
    int current = n;
    
    while (current > 0) {
        sum += current;
        current -= 2;
    }
    
    return sum;
}

int main(int argc, char *const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <integer>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    
    if (endptr == argv[1] || *endptr != '\0' || val < 0 || val > 2147483647) {
        fprintf(stderr, "Error: Invalid input. Please enter a positive integer.\n");
        return EXIT_FAILURE;
    }
    
    int n = (int)val;
    int result = sum_positive_integers(n);
    
    printf("Sum: %d\n", result);
    
    return EXIT_SUCCESS;
}