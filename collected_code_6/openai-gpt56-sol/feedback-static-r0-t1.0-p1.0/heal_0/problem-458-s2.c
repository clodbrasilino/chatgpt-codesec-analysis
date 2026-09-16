#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

static int rectangle_area(double length, double width, double *area)
{
    if (area == NULL || length < 0.0 || width < 0.0) {
        return -1;
    }

    *area = length * width;
    return 0;
}

int main(void)
{
    double length;
    double width;
    double area;

    errno = 0;

    if (scanf("%lf %lf", &length, &width) != 2) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (rectangle_area(length, width, &area) != 0) {
        fputs("Length and width must be non-negative\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%.2f\n", area) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}