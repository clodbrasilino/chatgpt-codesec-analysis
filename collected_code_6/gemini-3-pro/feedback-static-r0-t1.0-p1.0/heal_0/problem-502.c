#include <stdio.h>
#include <stdlib.h>

int find_remainder(int numerator, int denominator, int *remainder) {
    if (denominator == 0) {
        return -1;
    }
    *remainder = numerator % denominator;
    return 0;
}

int main(void) {
    int num1 = 0;
    int num2 = 0;
    int remainder = 0;
    int status = 0;

    printf("Enter numerator: ");
    if (scanf("%d", &num1) != 1) {
        fprintf(stderr, "Invalid input for numerator.\n");
        return EXIT_FAILURE;
    }

    printf("Enter denominator: ");
    if (scanf("%d", &num2) != 1) {
        fprintf(stderr, "Invalid input for denominator.\n");
        return EXIT_FAILURE;
    }

    status = find_remainder(num1, num2, &remainder);
    
    if (status != 0) {
        fprintf(stderr, "Error: Division by zero.\n");
        return EXIT_FAILURE;
    }

    printf("The remainder of %d divided by %d is %d.\n", num1, num2, remainder);

    return EXIT_SUCCESS;
}