#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979323846

double volume_of_sphere(double radius) {
    if (radius < 0) {
        return -1;
    }

    return (4.0 / 3.0) * PI * pow(radius, 3);
}

int main() {
    double radius, volume;
    
    printf("Enter the radius of the sphere: ");
    scanf("%lf", &radius);

    volume = volume_of_sphere(radius);
    if (volume < 0) {
        printf("Invalid radius entered.\n");
        return 1;
    }

    printf("The volume of the sphere is: %.2lf\n", volume);

    return 0;
}