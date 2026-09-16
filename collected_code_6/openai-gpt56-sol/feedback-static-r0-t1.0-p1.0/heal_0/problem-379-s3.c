#include <stdio.h>
#include <stdlib.h>

static int calculate_surface_area(double length, double width, double height,
                                  double *surface_area)
{
    if (length <= 0.0 || width <= 0.0 || height <= 0.0 ||
        surface_area == NULL) {
        return 0;
    }

    *surface_area = 2.0 * (length * width + length * height + width * height);
    return 1;
}

int main(void)
{
    double length;
    double width;
    double height;
    double surface_area;

    if (scanf("%lf %lf %lf", &length, &width, &height) != 3) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (!calculate_surface_area(length, width, height, &surface_area)) {
        fprintf(stderr, "Dimensions must be positive\n");
        return EXIT_FAILURE;
    }

    printf("%.2f\n", surface_area);
    return EXIT_SUCCESS;
}