#include <stdio.h>
#include <stdlib.h>

static int calculate_area(double length, double width, double *area)
{
    if (length < 0.0 || width < 0.0 || area == NULL) {
        return 0;
    }

    *area = length * width;
    return 1;
}

int main(void)
{
    double length;
    double width;
    double area;

    printf("Enter length and width: ");
    if (scanf("%lf %lf", &length, &width) != 2) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    if (!calculate_area(length, width, &area)) {
        fprintf(stderr, "Length and width must be non-negative.\n");
        return EXIT_FAILURE;
    }

    printf("Area: %.2f\n", area);
    return EXIT_SUCCESS;
}