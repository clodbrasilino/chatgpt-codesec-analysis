#include <stdio.h>
#include <stdlib.h>

int find_quotient(int dividend, int divisor) {
    if (divisor == 0) {
        fprintf(stderr, "Error: Division by zero is not allowed.\n");
        exit(EXIT_FAILURE);
    }
    return dividend / divisor;
}

int main(void) {
    int num1, num2, quotient;

    printf("Enter dividend: ");
    if (scanf("%d", &num1) != 1) {
        fprintf(stderr, "Error: Invalid input.\n");
        return EXIT_FAILURE;
    }

    printf("Enter divisor: ");
    if (scanf("%d", &num2) != 1) {
        fprintf(stderr, "Error: Invalid input.\n");
        return EXIT_FAILURE;
    }

    quotient = find_quotient(num1, num2);
    printf("The quotient is: %d\n", quotient);

    return EXIT_SUCCESS;
}