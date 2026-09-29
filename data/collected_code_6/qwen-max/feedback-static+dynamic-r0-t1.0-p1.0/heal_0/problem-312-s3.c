#include <stdio.h>
#include <math.h>

double cone_volume(double radius, double height) {
    return (1.0/3.0) * M_PI * pow(radius, 2) * height;
}

int main() {
    double r, h;
    printf("Enter the radius and height of the cone: ");
    if (scanf("%lf %lf", &r, &h) != 2) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }
    double volume = cone_volume(r, h);
    printf("The volume of the cone is: %.2f\n", volume);
    return 0;
}