#include <stdio.h>
#include <stdlib.h>

unsigned int lastTwoDigitsFactorial(unsigned long n) {
    if (n == 0 || n == 1) return 1;

    unsigned int result = 1;
    for (unsigned long i = 2; i <= n; ++i) {
        result *= i;
        while (result % 10 == 0) {
            result /= 10;
        }
        result %= 100;
    }
    return result;
}

int main() {
    unsigned long number;
    printf("Enter a number: ");
    if (scanf("%lu", &number) != 1) {
        return EXIT_FAILURE;
    }

    unsigned int lastTwoDigits = lastTwoDigitsFactorial(number);
    printf("Last two digits of factorial: %02u\n", lastTwoDigits);
    return EXIT_SUCCESS;
}