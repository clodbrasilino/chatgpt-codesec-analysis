#include <stdio.h>
#include <stdlib.h>

double calculate_parallelogram_area(double base, double side)
{
    if (base <= 0.0 || side <= 0.0)
    {
        exit(EXIT_FAILURE);
    }
    return base * side;
}

int main(void)
{
    double base, side;
    if (scanf("%lf %lf", &base, &side) == 2)
    {
        double area = calculate_parallelogram_area(base, side);
        printf("%.0f\n", area);
    }
    else
    {
        printf("0\n");
    }
    return 0;
}