#include <stdio.h>
#include <stdlib.h>

static int rectangle_perimeter(double length, double width, double *perimeter)
{
    if (perimeter == NULL || length < 0.0 || width < 0.0) {
        return 0;
    }

    *perimeter = 2.0 * (length + width);
    return 1;
}

int main(void)
{
    double length;
    double width;
    double perimeter;

    if (scanf("%lf %lf", &length, &width) != 2) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!rectangle_perimeter(length, width, &perimeter)) {
        fputs("Length and width must be nonnegative\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%.2f\n", perimeter);
    return EXIT_SUCCESS;
}