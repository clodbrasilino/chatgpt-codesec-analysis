#include <stdio.h>
#include <stdlib.h>

double surface_area_cuboid(double length, double width, double height) {
    if (length < 0 || width < 0 || height < 0) {
        fprintf(stderr, "Error: Dimensions must be non-negative.\n");
        exit(EXIT_FAILURE);
    }
    return 2 * (length * width + width * height + height * length);
}

int main(void) {
    double length, width, height;

    printf("Enter length, width, and height: ");
    if (scanf("%lf %lf %lf", &length, &width, &height) != 3) {
        fprintf(stderr, "Error: Invalid input.\n");
        return EXIT_FAILURE;
    }

    double area = surface_area_cuboid(length, width, height);
    printf("Surface area: %.2f\n", area);

    return EXIT_SUCCESS;
}