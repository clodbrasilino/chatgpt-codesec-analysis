#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int calculate_tetrahedron_area(double edge, double *area) {
    if (area == NULL) {
        return EXIT_FAILURE;
    }

    if (!isfinite(edge) || edge <= 0.0) {
        *area = 0.0;
        return EXIT_FAILURE;
    }

    *area = sqrt(3.0) * edge * edge;
    return EXIT_SUCCESS;
}

int main(void) {
    double edge = 5.0;
    double area;

    if (calculate_tetrahedron_area(edge, &area) == EXIT_SUCCESS) {
        printf("%f\n", area);
    } else {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}