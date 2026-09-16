#include <stdio.h>

double tetrahedron_volume(double edge_length) {
    return (edge_length * edge_length * edge_length) / (6.0 * sqrt(2.0));
}

int main() {
    double edge = 0.0;
    printf("Enter the edge length of the tetrahedron: ");
    if (scanf("%lf", &edge) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }
    if (edge <= 0) {
        fprintf(stderr, "Edge length must be positive.\n");
        return 1;
    }

    double volume = tetrahedron_volume(edge);
    printf("Volume of the tetrahedron: %f\n", volume);

    return 0;
}