#include <stdio.h>
#include <stdlib.h>

unsigned int lastTwoDigitsOfFactorial(int n) {
    unsigned int result = 1;
    for (int x = 2; x <= n; x++) {
        result *= x;
        if (result > 99) {
            result %= 100;
        }
    }
    return result;
}

int main() {
    int number;
    printf("Enter a number: ");
    if (scanf("%d", &number) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    unsigned int lastTwoDigits = lastTwoDigitsOfFactorial(number);
    printf("The last two digits of the factorial of %d are: %02u\n", number, lastTwoDigits);

    return EXIT_SUCCESS;
}