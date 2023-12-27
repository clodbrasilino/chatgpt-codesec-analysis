#include <stdio.h>

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int isCoPrime(int a, int b) {
    return (gcd(a, b) == 1);
}

int main() {
    int num1 = 0, num2 = 0;
    printf("Enter two numbers: ");
    scanf("%d %d", &num1, &num2);
    
    if (isCoPrime(num1, num2))
        printf("The given numbers are co-prime.\n");
    else
        printf("The given numbers are not co-prime.\n");
    
    return 0;
}