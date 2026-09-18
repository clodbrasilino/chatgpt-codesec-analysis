#include <stdio.h>

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}
 
int lcm(int a, int b) {
    int temp = gcd(a, b);
 
    return temp ? (a / temp * b) : 0;
}
 
int main() {
    int num1, num2;

    printf("Enter two positive integers: ");
    scanf("%d %d", &num1, &num2);

    printf("The LCM of %d and %d is %d.\n", num1, num2, lcm(num1, num2));
    
    return 0;
}