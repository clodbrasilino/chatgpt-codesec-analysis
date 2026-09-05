#include <stdio.h>
#include <stdbool.h>

bool isValidTriangle(double a, double b, double c)
{
    if (a <= 0.0 || b <= 0.0 || c <= 0.0)
    {
        return false;
    }

    if ((a + b > c) && (b + c > a) && (c + a > b))
    {
        return true;
    }

    return false;
}

int main(void)
{
    double a;
    double b;
    double c;

    if (scanf("%lf %lf %lf", &a, &b, &c) != 3)
    {
        return 1;
    }

    if (isValidTriangle(a, b, c))
    {
        printf("Valid triangle\n");
    }
    else
    {
        printf("Invalid triangle\n");
    }

    return 0;
}