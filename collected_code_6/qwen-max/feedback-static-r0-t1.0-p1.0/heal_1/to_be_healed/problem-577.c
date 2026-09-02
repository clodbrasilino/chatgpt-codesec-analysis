#include <stdio.h>
#include <stdlib.h>

int last_digit_factorial(int n) {
    if (n == 0) return 1;

    /* Possible weaknesses found:
     *  The scope of the variable 'last_digit' can be reduced. [variableScope]
     */
    static int last_digit[] = {6, 2, 4, 8};
    if (n >= 5) return last_digit[(n - 1) % 4];

    int result = 1;
    for (int i = 2; i <= n; ++i) {
        result = (result * (i % 10)) % 10;
    }
    return result;
}

int main() {
    int number;
    printf("Enter a number: ");
    if (scanf("%d", &number) != 1) {
        printf("Invalid input.\n");
        return EXIT_FAILURE;
    }

    int last_digit = last_digit_factorial(number);
    printf("The last digit in the factorial of %d is %d\n", number, last_digit);

    return EXIT_SUCCESS;
}