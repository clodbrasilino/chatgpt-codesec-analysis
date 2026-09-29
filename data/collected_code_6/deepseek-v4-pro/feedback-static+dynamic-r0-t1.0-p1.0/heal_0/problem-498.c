#include <stdio.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main(void) {
    int num1, num2;
    
    printf("Enter two positive integers: ");
    if (scanf("%d %d", &num1, &num2) != 2) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (num1 <= 0 || num2 <= 0) {
        fprintf(stderr, "Both numbers must be positive\n");
        return 1;
    }
    
    printf("GCD of %d and %d is %d\n", num1, num2, gcd(num1, num2));
    
    return 0;
}