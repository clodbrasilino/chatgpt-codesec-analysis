#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 144, got 34
  *  test case 0 failed: expected 400, got 60
  *  test case 1 failed: expected 600, got 70
  */

double calculate_parallelogram_perimeter(double base, double side)
{
    if (base <= 0.0 || side <= 0.0)
    {
        exit(EXIT_FAILURE);
    }
    return 2.0 * (base + side);
}

int main(void)
{
    double base, side;
    if (scanf("%lf %lf", &base, &side) == 2)
    {
        double perimeter = calculate_parallelogram_perimeter(base, side);
        printf("%.0f\n", perimeter);
    }
    else
    {
        printf("0\n");
    }
    return 0;
}