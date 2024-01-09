#include <stdio.h>
#include <math.h>

double calculateTetrahedron(double a) {
    double volume;
    
    volume = (sqrt(2)) / 12 * pow(a, 3);
    
    return volume;
}

int main() {
    double sideLength, area;
    
    printf("Enter the side length of the tetrahedron: ");
    scanf("%lf", &sideLength);
    
    area = calculateTetrahedron(sideLength);
    
    printf("The area of the tetrahedron is: %lf\n", area);
    
    return 0;
}