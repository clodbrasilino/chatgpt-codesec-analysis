#include <stdio.h>

double calculate_parallelogram_area(double base, double height);

int main(void)
{
    double base = 0.0;
    double height = 0.0;
    double area = 0.0;
    int input_result = 0;

    printf("Enter the base of the parallelogram: ");
    input_result = scanf("%lf", &base);
    if (input_result != 1 || base < 0.0)
    {
        fprintf(stderr, "Error: Invalid base input. Please enter a non-negative number.\n");
        return 1;
    }

    printf("Enter the height of the parallelogram: ");
    input_result = scanf("%lf", &height);
    if (input_result != 1 || height < 0.0)
    {
        fprintf(stderr, "Error: Invalid height input. Please enter a non-negative number.\n");
        return 1;
    }

    area = calculate_parallelogram_area(base, height);
    printf("Area of the parallelogram: %.2f\n", area);

    return 0;
}

double calculate_parallelogram_area(double base, double height)
{
    return base * height;
}