#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

__uint128_t calculateDifference(int n) {
    if (n < 1) {
        return 0;
    }
    
    __uint128_t sum = (__uint128_t)n * (n + 1) / 2;
    __uint128_t sumOfCubes = sum * sum;
    
    return sumOfCubes - sum;
}

void print_uint128(__uint128_t value) {
    if (value == 0) {
        printf("0");
        return;
    }
    
    char buffer[64];
    size_t i = 0;
    size_t buffer_size = sizeof(buffer);
    
    while (value > 0 && i < buffer_size - 1) {
        buffer[i++] = '0' + (value % 10);
        value /= 10;
    }
    
    buffer[i] = '\0';
    
    for (size_t j = i; j > 0; j--) {
        printf("%c", buffer[j - 1]);
    }
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
    print_uint128(result);
    printf("\n");
    
    return 0;
}