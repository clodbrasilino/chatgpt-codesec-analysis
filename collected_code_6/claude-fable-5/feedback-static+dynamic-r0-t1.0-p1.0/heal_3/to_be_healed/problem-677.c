#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static void swap(double *x, double *y)
{
    double t = *x;
    *x = *y;
    *y = t;
}
 /* Possible weaknesses found:
  *  test case 2 failed: expected True, got 0
  *  test case 0 failed: expected False, got 1
  */

int is_valid_triangle(double a, double b, double c)
{
    if (isnan(a) || isnan(b) || isnan(c))
    {
        return 0;
    }
    if (isinf(a) || isinf(b) || isinf(c))
    {
        return 0;
    }
    if (a <= 0.0 || b <= 0.0 || c <= 0.0)
    {
        return 0;
    }

    if (a > b)
    {
        swap(&a, &b);
    }
    if (b > c)
    {
        swap(&b, &c);
    }
    if (a > b)
    {
        swap(&a, &b);
    }

    if (a + b > c)
    {
        return 1;
    }
    return 0;
}

int main(void)
{
    double a;
    double b;
    double c;

    printf("Enter the three sides of the triangle: ");
    if (scanf("%lf %lf %lf", &a, &b, &c) != 3)
    {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (is_valid_triangle(a, b, c))
    {
        printf("The triangle is valid.\n");
    }
    else
    {
        printf("The triangle is not valid.\n");
    }

    return EXIT_SUCCESS;
}