#include <stdio.h>
#include <math.h>

double calculateTetrahedronVolume(double edge) {
    return (pow(edge, 3) * sqrt(2)) / 12;
}

int main() {
    double edge;
    printf("Enter the edge length of the tetrahedron: ");
    scanf("%lf", &edge);
    printf("The volume of the tetrahedron is: %.2lf\n", calculateTetrahedronVolume(edge));
    return 0;
}