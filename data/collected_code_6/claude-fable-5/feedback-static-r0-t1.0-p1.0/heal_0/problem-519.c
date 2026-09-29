#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double tetrahedron_volume(double edge)
{
    return (edge * edge * edge) / (6.0 * sqrt(2.0));
}

int main(void)
{
    double edge = 0.0;
    double volume = 0.0;
    int result = 0;

    printf("Enter the edge length of the tetrahedron: ");
    result = scanf("%lf", &edge);

    if (result != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (edge <= 0.0 || !isfinite(edge)) {
        fprintf(stderr, "Error: edge length must be a positive finite number.\n");
        return EXIT_FAILURE;
    }

    volume = tetrahedron_volume(edge);

    if (!isfinite(volume)) {
        fprintf(stderr, "Error: computation overflow.\n");
        return EXIT_FAILURE;
    }

    printf("Volume of the tetrahedron: %.6f\n", volume);

    return EXIT_SUCCESS;
}