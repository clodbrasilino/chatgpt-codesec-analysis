#include <stdio.h>

int firstDigitFactorial(int n) {
    if (n < 0) {
        return -1;
    }
    
    int fact = 1;
    while (n > 0) {
        fact *= n;
        n--;
    }
    
    while (fact >= 10) {
        fact /= 10;
    }
    
    return fact;
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    
    int firstDigit = firstDigitFactorial(n);
    printf("The first digit in the factorial of %d is %d", n, firstDigit);
    
    return 0;
}