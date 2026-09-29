#include <stdio.h>
#include <stdlib.h>

double lateral_surface_area(double length, double width, double height);

int main(void) {
    double length = 0.0;
    double width = 0.0;
    double height = 0.0;
    double area = 0.0;
    int result = 0;

    result = scanf("%lf %lf %lf", &length, &width, &height);

    if (result != 3) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (length < 0.0 || width < 0.0 || height < 0.0) {
        fprintf(stderr, "Dimensions cannot be negative\n");
        return EXIT_FAILURE;
    }

    area = lateral_surface_area(length, width, height);

    printf("%f\n", area);

    return EXIT_SUCCESS;
}

double lateral_surface_area(double length, double width, double height) {
    return 2.0 * height * (length + width);
}