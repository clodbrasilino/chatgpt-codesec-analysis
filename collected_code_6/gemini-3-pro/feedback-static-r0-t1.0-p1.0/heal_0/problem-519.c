#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double calculate_tetrahedron_volume(double edge_length);

double calculate_tetrahedron_volume(double edge_length) {
    if (edge_length < 0.0) {
        return -1.0;
    }
    return (sqrt(2.0) / 12.0) * pow(edge_length, 3.0);
}

int main(void) {
    double edge_length = 5.0;
    double volume;

    if (edge_length < 0.0) {
        fprintf(stderr, "Error: Edge length cannot be negative.\n");
        return EXIT_FAILURE;
    }

    volume = calculate_tetrahedron_volume(edge_length);

    if (volume < 0.0) {
        fprintf(stderr, "Error: Invalid volume calculated.\n");
        return EXIT_FAILURE;
    }

    printf("%.6f\n", volume);

    return EXIT_SUCCESS;
}