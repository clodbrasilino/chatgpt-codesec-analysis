#include <stdio.h>

int gcd(int a, int b) {
    if (b == 0) {
        return a;
    } else {
        return gcd(b, a % b);
    }
}

int main() {
    int num1 = 0, num2 = 0;
    
    printf("Enter two integers: ");
    scanf("%d %d", &num1, &num2);
    
    if (num2 != 0) {
        printf("The greatest common divisor is %d\n", gcd(num1, num2));
    } else {
        printf("Error: Division by zero is undefined\n");
    }
    
    return 0;
}