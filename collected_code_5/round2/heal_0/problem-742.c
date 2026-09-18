#include <math.h>
#include <stdio.h>

double calculateTetrahedronArea(double edge) {
    if(edge <= 0) {
        printf("Error: Edge length of tetrahedron should be positive.\n");
        return -1.0;
    }
    return sqrt(3) * pow(edge, 2);
}

int main() {
    double edge;
    printf("Enter the edge length of the tetrahedron: ");
    if(scanf("%lf", &edge) != 1) {
        printf("Error reading the edge length.\n");
        return 1;
    }
    double area = calculateTetrahedronArea(edge);
    if(area != -1.0) {
        printf("The area of the tetrahedron with edge length %.2lf is: %.2lf\n", edge, area);
    }
    return 0;
}