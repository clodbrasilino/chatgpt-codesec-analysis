#include <stdio.h>

double cube_surface_area(double side_length)
{
    return 6.0 * side_length * side_length;
}

int main(void)
{
    double side_length;
    double surface_area;
    int scan_result;

    printf("Enter the side length of the cube: ");
    scan_result = scanf("%lf", &side_length);

    if (scan_result != 1)
    {
        fprintf(stderr, "Error: Invalid input.\n");
        return 1;
    }

    if (side_length < 0.0)
    {
        fprintf(stderr, "Error: Side length cannot be negative.\n");
        return 1;
    }

    surface_area = cube_surface_area(side_length);
    printf("Surface area of the cube: %.2f\n", surface_area);

    return 0;
}