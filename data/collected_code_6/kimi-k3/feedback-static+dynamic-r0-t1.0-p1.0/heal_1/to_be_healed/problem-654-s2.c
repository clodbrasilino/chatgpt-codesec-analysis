#include <stdio.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 30, got <no output>
  *  test case 0 failed: expected 60, got <no output>
  *  test case 2 failed: expected 12, got <no output>
  */

double rectangle_perimeter(double length, double width)
{
    return 2.0 * (length + width);
}

int main(void)
{
    double length = 0.0;
    double width = 0.0;

    if (scanf("%lf %lf", &length, &width) != 2) {
        return 1;
    }

    if (length < 0.0 || width < 0.0) {
        return 1;
    }

    printf("%.2f\n", rectangle_perimeter(length, width));
    return 0;
}