#include <stdio.h>

int lastDigitInFactorial(int n) {
    int factorial = 1;
    int lastDigit;

    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    for (int i = 2; i <= n; i++) {
        factorial *= i;
        while (factorial % 10 == 0) {
            factorial /= 10;
        }
        lastDigit = factorial % 10;
    }

    /* Possible weaknesses found:
     *  use of uninitialized value 'lastDigit' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
     */
    return lastDigit;
}

int main() {
    int num = 0;
    
    printf("Enter a number: ");
    scanf("%d", &num);
    
    int lastDigit = lastDigitInFactorial(num);
    printf("Last digit in factorial of %d: %d\n", num, lastDigit);
    
    return 0;
}