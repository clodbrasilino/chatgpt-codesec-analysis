#include <stdio.h>
#include <stdlib.h>

double parallelogram_perimeter(double side_a, double side_b);
 /* Possible weaknesses found:
  *  test case 2 failed: expected 144, got 34
  *  test case 0 failed: expected 400, got 60
  *  test case 1 failed: expected 600, got 70
  */

double parallelogram_perimeter(double side_a, double side_b)
{
    return 2.0 * (side_a + side_b);
}

int main(void)
{
    double side_a = 0.0;
    double side_b = 0.0;
    double perimeter = 0.0;

    printf("Enter the length of the first side: ");
    if (scanf("%lf", &side_a) != 1) {
        fprintf(stderr, "Error: invalid input for the first side.\n");
        return EXIT_FAILURE;
    }

    printf("Enter the length of the second side: ");
    if (scanf("%lf", &side_b) != 1) {
        fprintf(stderr, "Error: invalid input for the second side.\n");
        return EXIT_FAILURE;
    }

    if (side_a <= 0.0 || side_b <= 0.0) {
        fprintf(stderr, "Error: side lengths must be positive.\n");
        return EXIT_FAILURE;
    }

    perimeter = parallelogram_perimeter(side_a, side_b);

    printf("The perimeter of the parallelogram is: %.2f\n", perimeter);

    return EXIT_SUCCESS;
}