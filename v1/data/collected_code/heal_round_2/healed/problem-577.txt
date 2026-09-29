#include <stdio.h>

int lastDigitInFactorial(int n) {
    int factorial = 1;
    int lastDigit = 1;

    for (int i = 2; i <= n; i++) {
        factorial *= i;
        while (factorial % 10 == 0 && factorial != 0) {
            factorial /= 10;
        }
        lastDigit = factorial % 10;
    }

    return lastDigit;
}

int main() {
    int num = 0;

    printf("Enter a number: ");
    scanf("%d", &num);
    
    if(num >= 0){
        int lastDigit = lastDigitInFactorial(num);
        printf("Last digit in factorial of %d: %d\n", num, lastDigit);
    }
    
    return 0;
}