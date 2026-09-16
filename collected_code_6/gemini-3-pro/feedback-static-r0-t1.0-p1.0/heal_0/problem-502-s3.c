#include <stdio.h>
#include <stdlib.h>

int find_remainder(int numerator, int denominator);

int main(void) {
    int num1 = 0;
    int num2 = 0;
    int result = 0;

    printf("Enter numerator: ");
    if (scanf("%d", &num1) != 1) {
        fprintf(stderr, "Error: Invalid input for numerator.\n");
        return EXIT_FAILURE;
    }

    printf("Enter denominator: ");
    if (scanf("%d", &num2) != 1) {
        fprintf(stderr, "Error: Invalid input for denominator.\n");
        return EXIT_FAILURE;
    }

    if (num2 == 0) {
        fprintf(stderr, "Error: Division by zero is not allowed.\n");
        return EXIT_FAILURE;
    }

    result = find_remainder(num1, num2);
    printf("The remainder of %d divided by %d is %d\n", num1, num2, result);

    return EXIT_SUCCESS;
}

int find_remainder(int numerator, int denominator) {
    if (denominator == 0) {
        fprintf(stderr, "Error: Division by zero in find_remainder.\n");
        exit(EXIT_FAILURE);
    }
    return numerator % denominator;
}