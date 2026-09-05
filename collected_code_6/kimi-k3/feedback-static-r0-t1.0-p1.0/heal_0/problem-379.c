#include <stdio.h>

double calculate_cuboid_surface_area(double length, double width, double height)
{
    return 2.0 * (length * width + width * height + height * length);
}

int main(void)
{
    double length = 0.0;
    double width = 0.0;
    double height = 0.0;
    double surface_area = 0.0;
    int input_count = 0;

    printf("Enter length, width, and height of the cuboid: ");
    input_count = scanf("%lf %lf %lf", &length, &width, &height);

    if (input_count != 3)
    {
        fprintf(stderr, "Error: Invalid input. Please enter three numeric values.\n");
        return 1;
    }

    if (length <= 0.0 || width <= 0.0 || height <= 0.0)
    {
        fprintf(stderr, "Error: Dimensions must be positive values.\n");
        return 1;
    }

    surface_area = calculate_cuboid_surface_area(length, width, height);
    printf("Surface area of the cuboid: %.2lf\n", surface_area);

    return 0;
}