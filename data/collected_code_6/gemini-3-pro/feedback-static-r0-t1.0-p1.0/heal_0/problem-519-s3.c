#include <stdio.h>
#include <math.h>

double calculate_tetrahedron_volume(double edge_length) {
    if (edge_length < 0.0) {
        return -1.0;
    }
    return (pow(edge_length, 3.0) / (6.0 * sqrt(2.0)));
}

int main(void) {
    double edge_length;
    double volume;

    if (scanf("%lf", &edge_length) != 1) {
        return 1;
    }

    volume = calculate_tetrahedron_volume(edge_length);

    if (volume < 0.0) {
        return 1;
    }

    printf("%f\n", volume);

    return 0;
}