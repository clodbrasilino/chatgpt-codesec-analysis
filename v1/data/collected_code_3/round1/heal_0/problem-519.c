#include <stdio.h>
#include <math.h>

double volume_of_tetrahedron(double edge) {
    return (pow(edge, 3) * sqrt(2)) / 12;
}

int main() {
    double edge;

    printf("Enter the edge length of the tetrahedron: ");
    scanf("%lf", &edge);

    printf("The volume of the tetrahedron is: %.2lf\n", volume_of_tetrahedron(edge));

    return 0;
}