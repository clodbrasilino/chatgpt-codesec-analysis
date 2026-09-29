#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>

__uint128_t calculateDifference(int n) {
    if (n < 1) {
        return 0;
    }
    
    __uint128_t sum = (__uint128_t)n * (n + 1) / 2;
    __uint128_t sumOfCubes = sum * sum;
    
    return sumOfCubes - sum;
}

int print_uint128(__uint128_t value) {
    if (value == 0) {
        return printf("0");
    }
    
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[40];
    size_t i = 0;
    size_t buffer_size = sizeof(buffer);
    
    while (value > 0 && i < buffer_size - 1) {
        buffer[i++] = '0' + (value % 10);
        value /= 10;
    }
    
    if (value > 0) {
        return -1;
    }
    
    buffer[i] = '\0';
    
    for (size_t j = i; j > 0; j--) {
        if (printf("%c", buffer[j - 1]) < 0) {
            return -1;
        }
    }
    
    return 0;
}

int main(void) {
    int n;
    
    printf("Enter a positive integer: ");
    
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (n < 1) {
        fprintf(stderr, "Please enter a positive integer\n");
        return 1;
    }
    
    __uint128_t result = calculateDifference(n);
    printf("Difference: ");
    if (print_uint128(result) < 0) {
        fprintf(stderr, "Error printing result\n");
        return 1;
    }
    printf("\n");
    
    return 0;
}