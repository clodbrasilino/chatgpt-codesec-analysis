#include <stdio.h>
#include <math.h>

double calcTetrahedronVolume(double a) {
    if(a <= 0) {
        return 0.0;
    }
    return (pow(a, 3) * sqrt(2)) / 12.0;
}

int main() {
    double a;
    printf("Enter the side length of the tetrahedron: ");
    if(scanf("%lf", &a) != 1) {
        printf("Invalid input! Please enter a number.\n");
        return 1;
    }
  
    double volume = calcTetrahedronVolume(a);
    if(volume == 0.0) {
        printf("The side length should be a positive number.\n");
        return 1;
    }
  
    printf("The volume of the tetrahedron with side length %.2lf is %.2lf\n", a, volume);
    return 0;
}