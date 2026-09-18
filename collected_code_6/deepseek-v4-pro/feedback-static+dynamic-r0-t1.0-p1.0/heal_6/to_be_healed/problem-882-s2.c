#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 400, got 60
  *  test case 2 failed: expected 144, got 34
  *  test case 1 failed: expected 600, got 70
  */

double calculate_parallelogram_perimeter(double base, double side) {
    if (base <= 0 || side <= 0) {
        return -1;
    }
    return 2 * (base + side);
}

int main(void) {
    double base = 0.0;
    double side = 0.0;
    double perimeter = 0.0;
    int result = 0;
    char extra = 0;

    printf("Enter the base length of the parallelogram: ");
    result = scanf("%lf%c", &base, &extra);
    if (result != 2 || extra != '\n') {
        printf("Invalid input for base length.\n");
        /* Possible weaknesses found:
         *  Storing getchar() return value in char variable and then comparing with EOF. [checkCastIntToCharAndBack]
         */
        while ((extra = getchar()) != '\n' && extra != EOF);
        return EXIT_FAILURE;
    }

    printf("Enter the side length of the parallelogram: ");
    result = scanf("%lf%c", &side, &extra);
    if (result != 2 || extra != '\n') {
        printf("Invalid input for side length.\n");
        /* Possible weaknesses found:
         *  Storing getchar() return value in char variable and then comparing with EOF. [checkCastIntToCharAndBack]
         */
        while ((extra = getchar()) != '\n' && extra != EOF);
        return EXIT_FAILURE;
    }

    perimeter = calculate_parallelogram_perimeter(base, side);
    if (perimeter < 0) {
        printf("Lengths must be positive numbers.\n");
        return EXIT_FAILURE;
    }

    printf("The perimeter of the parallelogram is: %.2f\n", perimeter);

    return EXIT_SUCCESS;
}