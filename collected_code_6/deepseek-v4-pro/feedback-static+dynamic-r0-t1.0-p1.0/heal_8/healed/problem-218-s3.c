#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int min_operations(int a, int b) {
    unsigned int xor_result;
    int count = 0;
    
    if (a == b) return 0;
    
    xor_result = (unsigned int)a ^ (unsigned int)b;
    
    while (xor_result != 0) {
        count += (int)(xor_result & 1U);
        xor_result >>= 1;
    }
    
    return count;
}

int main(void) {
    int num1, num2;
    
    printf("Enter first number: ");
    if (scanf("%d", &num1) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    printf("Enter second number: ");
    if (scanf("%d", &num2) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    printf("Minimum operations required: %d\n", min_operations(num1, num2));
    
    return 0;
}