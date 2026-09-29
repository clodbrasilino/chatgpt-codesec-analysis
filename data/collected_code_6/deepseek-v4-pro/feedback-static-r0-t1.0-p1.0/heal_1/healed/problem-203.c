#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

int hamming_distance(int a, int b) {
    unsigned int xor_result = (unsigned int)(a ^ b);
    int distance = 0;
    
    while (xor_result != 0) {
        distance += xor_result & 1;
        xor_result >>= 1;
    }
    
    return distance;
}

int main(int argc, const char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <int1> <int2>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    char *endptr1, *endptr2;
    errno = 0;
    
    long val1 = strtol(argv[1], &endptr1, 10);
    if (errno == ERANGE || val1 > INT_MAX || val1 < INT_MIN || *endptr1 != '\0') {
        fprintf(stderr, "Error: '%s' is not a valid integer\n", argv[1]);
        return EXIT_FAILURE;
    }
    
    errno = 0;
    long val2 = strtol(argv[2], &endptr2, 10);
    if (errno == ERANGE || val2 > INT_MAX || val2 < INT_MIN || *endptr2 != '\0') {
        fprintf(stderr, "Error: '%s' is not a valid integer\n", argv[2]);
        return EXIT_FAILURE;
    }
    
    int num1 = (int)val1;
    int num2 = (int)val2;
    int result = hamming_distance(num1, num2);
    
    printf("Hamming distance between %d and %d is %d\n", num1, num2, result);
    
    return EXIT_SUCCESS;
}