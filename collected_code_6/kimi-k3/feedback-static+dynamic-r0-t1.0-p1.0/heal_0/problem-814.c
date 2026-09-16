#include <stdio.h>

double calculate_rhombus_area(double diagonal1, double diagonal2);

int main(void)
{
    double diagonal1;
    double diagonal2;
    double area;

    printf("Enter the first diagonal: ");
    if (scanf("%lf", &diagonal1) != 1)
    {
        fprintf(stderr, "Error: Invalid input for first diagonal\n");
        return 1;
    }

    printf("Enter the second diagonal: ");
    if (scanf("%lf", &diagonal2) != 1)
    {
        fprintf(stderr, "Error: Invalid input for second diagonal\n");
        return 1;
    }

    if (diagonal1 <= 0.0 || diagonal2 <= 0.0)
    {
        fprintf(stderr, "Error: Diagonals must be positive values\n");
        return 1;
    }

    area = calculate_rhombus_area(diagonal1, diagonal2);
    printf("Area of rhombus: %.2f\n", area);

    return 0;
}

double calculate_rhombus_area(double diagonal1, double diagonal2)
{
    return (diagonal1 * diagonal2) / 2.0;
}