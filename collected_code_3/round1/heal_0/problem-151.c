#include <stdio.h>

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int areCoprime(int a, int b) {
    if (gcd(a, b) == 1)
        return 1;
    else
        return 0;
}

int main() {
    int num1, num2;
    printf("Enter two numbers: ");
    scanf("%d %d", &num1, &num2);
    if (areCoprime(num1, num2))
        printf("The numbers are co-prime\n");
    else
        printf("The numbers are not co-prime\n");
    return 0;
}