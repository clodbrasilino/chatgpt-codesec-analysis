#include <stdio.h>
#include <math.h>

double calculateTetrahedronArea(double edge) {
    return sqrt(3) * pow(edge, 2);
}

double calculateTetrahedronVolume(double edge) {
    return pow(edge, 3) / (6 * sqrt(2));
}

int main() {
    double edge;
    printf("Enter the edge length of the tetrahedron: ");
    scanf("%lf", &edge);

    double area = calculateTetrahedronArea(edge);
    double volume = calculateTetrahedronVolume(edge);

    printf("Area of the tetrahedron: %.2lf\n", area);
    printf("Volume of the tetrahedron: %.2lf\n", volume);

    return 0;
}