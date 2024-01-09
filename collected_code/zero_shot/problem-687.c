#include <stdio.h>

int gcd(int a, int b) {
    if (b == 0) {
        return a;
    } else {
        return gcd(b, a % b);
    }
}

int main() {
    int num1, num2;
    
    printf("Enter two integers: ");
    scanf("%d %d", &num1, &num2);
    
    printf("The greatest common divisor is %d\n", gcd(num1, num2));
    
    return 0;
}