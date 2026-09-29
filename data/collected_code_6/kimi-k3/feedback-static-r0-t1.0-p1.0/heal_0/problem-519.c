#include <stdio.h>
#include <math.h>

double calculate_tetrahedron_volume(double edge_length) {
    if (edge_length < 0) {
        return -1.0;
    }
    return pow(edge_length, 3) / (6 * sqrt(2));
}

int main() {
    double edge_length;
    printf("Enter the edge length of the tetrahedron: ");
    if (scanf("%lf", &edge_length) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    double volume = calculate_tetrahedron_volume(edge_length);
    if (volume < 0) {
        printf("Invalid edge length\n");
        return 1;
    }
    printf("Volume of the tetrahedron: %lf\n", volume);
    return 0;
}