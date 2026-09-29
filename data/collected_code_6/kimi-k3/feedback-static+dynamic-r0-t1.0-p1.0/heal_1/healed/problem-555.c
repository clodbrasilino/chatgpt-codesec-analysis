#include <stdio.h>
#include <stdint.h>

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
    int i = 0;
    
    while (value > 0) {
        buffer[i++] = '0' + (value % 10);
        value /= 10;
    }
    
    for (int j = i - 1; j >= 0; j--) {
        printf("%c", buffer[j]);
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