#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 144, got <no output>
  *  test case 1 failed: expected 600, got <no output>
  *  test case 0 failed: expected 400, got <no output>
  */

double calculate_parallelogram_perimeter(double base, double side)
{
    if (base <= 0.0 || side <= 0.0)
    {
        fprintf(stderr, "Invalid input: dimensions must be strictly positive.\n");
        exit(EXIT_FAILURE);
    }
    return 2.0 * (base + side);
}

int main(void)
{
    double base = 5.0;
    double side = 3.0;
    double perimeter = calculate_parallelogram_perimeter(base, side);
    printf("%f\n", perimeter);
    return 0;
}