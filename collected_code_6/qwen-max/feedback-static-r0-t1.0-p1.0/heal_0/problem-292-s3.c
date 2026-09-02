#include <stdio.h>
#include <stdlib.h>

int divide(int a, int b, int *quotient) {
    if (b == 0) {
        return -1;
    }
    *quotient = a / b;
    return 0;
}

int main() {
    int num1, num2, quotient, result;

    printf("Enter the first number: ");
    if (scanf("%d", &num1) != 1) {
        fprintf(stderr, "Invalid input for the first number.\n");
        return EXIT_FAILURE;
    }

    printf("Enter the second number: ");
    if (scanf("%d", &num2) != 1) {
        fprintf(stderr, "Invalid input for the second number.\n");
        return EXIT_FAILURE;
    }

    result = divide(num1, num2, &quotient);
    if (result == -1) {
        fprintf(stderr, "Division by zero is not allowed.\n");
        return EXIT_FAILURE;
    }

    printf("The quotient of %d divided by %d is %d\n", num1, num2, quotient);

    return EXIT_SUCCESS;
}