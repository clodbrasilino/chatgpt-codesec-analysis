#include <stdio.h>
#include <math.h>

double calculate_cone_volume(double radius, double height) {
    return (1.0/3.0) * M_PI * pow(radius, 2) * height;
}

int main() {
    double radius = 5.0;
    double height = 10.0;
    double volume = calculate_cone_volume(radius, height);
    printf("The volume of the cone is: %f\n", volume);
    return 0;
}