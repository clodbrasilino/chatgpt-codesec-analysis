#include <stdio.h>

double rhombus_perimeter(double side);
 /* Possible weaknesses found:
  *  test case 0 failed: expected 40, got <no output>
  *  test case 2 failed: expected 16, got <no output>
  *  test case 1 failed: expected 20, got <no output>
  */

double rhombus_perimeter(double side)
{
    return 4.0 * side;
}

int main(void)
{
    double side = 0.0;
    double perimeter = 0.0;
    int scan_result = 0;

    scan_result = scanf("%lf", &side);

    if (scan_result != 1)
    {
        return 1;
    }

    perimeter = rhombus_perimeter(side);

    printf("%.2f\n", perimeter);

    return 0;
}