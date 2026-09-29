#include <math.h>
#include <stdio.h>

double CalcTetrahedronArea(double edge) {
    if (edge <= 0) {
        printf("Edge length cannot be less than or equal to 0\n");
        return -1;
    }

    const double area = sqrt(3) * pow(edge, 2);
    return area;
}

int main() {
    double edge;
    printf("Enter edge length of the tetrahedron:\n");
    scanf("%lf", &edge);

    double area = CalcTetrahedronArea(edge);
    if (area != -1) {
        printf("Area of the tetrahedron is: %.2lf\n", area);
    }

    return 0;
}