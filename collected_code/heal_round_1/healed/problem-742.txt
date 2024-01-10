#include <stdio.h>
#include <math.h>

double calculateTetrahedron(double a) {
    double volume;
    
    volume = (sqrt(2)) / 12 * pow(a, 3);
    
    return volume;
}

int main() {
    double sideLength = 0.0, volume = 0.0;
    
    printf("Enter the side length of the tetrahedron: ");
    scanf("%lf", &sideLength);
    
    volume = calculateTetrahedron(sideLength);
    
    printf("The volume of the tetrahedron is: %lf\n", volume);
    
    return 0;
}