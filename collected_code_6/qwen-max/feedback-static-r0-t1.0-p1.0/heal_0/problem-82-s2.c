#include <stdio.h>
#include <math.h>

double volume_of_sphere(double radius) {
    return (4.0 / 3.0) * M_PI * pow(radius, 3);
}

int main() {
    double r;
    printf("Enter the radius of the sphere: ");
    scanf("%lf", &r);
    if (r < 0) {
        printf("Radius cannot be negative.\n");
        return 1;
    }
    double volume = volume_of_sphere(r);
    printf("Volume of the sphere: %.2f\n", volume);
    return 0;
}