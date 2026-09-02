#include <stdio.h>

double cuboid_volume(double length, double width, double height) {
    if (length < 0 || width < 0 || height < 0) {
        return -1.0;
    }
    return length * width * height;
}

int main(void) {
    double length, width, height;
    
    printf("Enter length, width, and height of cuboid: ");
    if (scanf("%lf %lf %lf", &length, &width, &height) != 3) {
        printf("Invalid input\n");
        return 1;
    }
    
    double volume = cuboid_volume(length, width, height);
    if (volume < 0) {
        printf("Error: dimensions cannot be negative\n");
        return 1;
    }
    
    printf("Volume of cuboid: %.2f\n", volume);
    return 0;
}