#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double tetrahedron_area(double edge)
{
    return sqrt(3.0) * edge * edge;
}

int main(void)
{
    double edge = 0.0;
    double area = 0.0;

    printf("Enter the edge length of the tetrahedron: ");

    if (scanf("%lf", &edge) != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (edge <= 0.0) {
        fprintf(stderr, "Error: edge length must be positive.\n");
        return EXIT_FAILURE;
    }

    if (!isfinite(edge)) {
        fprintf(stderr, "Error: edge length must be a finite number.\n");
        return EXIT_FAILURE;
    }

    area = tetrahedron_area(edge);

    if (!isfinite(area)) {
        fprintf(stderr, "Error: computation overflow.\n");
        return EXIT_FAILURE;
    }

    printf("Surface area of the tetrahedron: %f\n", area);

    return EXIT_SUCCESS;
}