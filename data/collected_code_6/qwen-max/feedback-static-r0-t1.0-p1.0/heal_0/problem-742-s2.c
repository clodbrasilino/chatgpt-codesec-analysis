#include <stdio.h>
#include <math.h>

double calculate_tetrahedron_area(double edge) {
    return sqrt(3) * pow(edge, 2);
}

int main() {
    double edge, area;
    printf("Enter the edge length of the tetrahedron: ");
    if (scanf("%lf", &edge) == 1) {
        area = calculate_tetrahedron_area(edge);
        printf("The area of the tetrahedron is: %f\n", area);
    } else {
        printf("Invalid input. Please enter a valid number.\n");
    }
    return 0;
}