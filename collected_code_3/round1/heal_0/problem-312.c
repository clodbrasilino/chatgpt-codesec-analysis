#include <stdio.h>
#include <math.h>

double coneVolume(double radius, double height) {
    return (M_PI * radius * radius * height) / 3.0;
}

int main() {
    double radius, height, volume;

    printf("Enter radius of the cone: ");
    scanf("%lf", &radius);
    printf("Enter height of the cone: ");
    scanf("%lf", &height);

    volume = coneVolume(radius, height);

    printf("Volume of the cone is: %.2lf\n", volume);

    return 0;
}