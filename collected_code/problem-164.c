#include <stdio.h>

int sumOfDivisors(int n) {
    int sum = 0;
    for(int i = 1; i <= n/2; i++) {
        if(n % i == 0) {
            sum += i;
        }
    }
    return sum;
}

int divisorsSumSame(int num1, int num2) {
    return sumOfDivisors(num1) == sumOfDivisors(num2);
}

int main() {
    int num1, num2;
    printf("Enter two numbers: ");
    scanf("%d %d", &num1, &num2);
    
    if(divisorsSumSame(num1, num2)) {
        printf("The sum of divisors of both numbers are same.\n");
    }
    else {
        printf("The sum of divisors of both numbers are different.\n");
    }
    
    return 0;
}