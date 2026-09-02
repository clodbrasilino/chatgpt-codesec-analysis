#include <stdio.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int find_common_divisor(int num1, int num2) {
    if (num1 == 0 || num2 == 0) {
        return 0;
    }
    
    if (num1 < 0) num1 = -num1;
    if (num2 < 0) num2 = -num2;
    
    return gcd(num1, num2);
}

int main(void) {
    int num1, num2;
    
    printf("Enter two numbers: ");
    if (scanf("%d %d", &num1, &num2) != 2) {
        fprintf(stderr, "Error: Invalid input\n");
        return 1;
    }
    
    int result = find_common_divisor(num1, num2);
    
    if (result == 0) {
        printf("No common divisor found (both numbers are zero)\n");
    } else {
        printf("Common divisor: %d\n", result);
    }
    
    return 0;
}