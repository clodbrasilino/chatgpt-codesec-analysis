#include <stdio.h>
#include <math.h>

double calculate_cone_volume(double radius, double height);

int main(void) {
    double radius = 5.0;
    double height = 10.0;
    double volume;

    volume = calculate_cone_volume(radius, height);
    printf("Volume of cone: %f\n", volume);

    return 0;
}

double calculate_cone_volume(double radius, double height) {
    double volume;

    volume = (1.0 / 3.0) * M_PI * pow(radius, 2) * height;

    return volume;
}