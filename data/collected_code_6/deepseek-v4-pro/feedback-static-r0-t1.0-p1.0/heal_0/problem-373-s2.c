#include <stdio.h>

double cuboid_volume(double length, double width, double height) {
    return length * width * height;
}

int main(void) {
    double length, width, height, volume;

    printf("Enter length: ");
    if (scanf("%lf", &length) != 1) {
        printf("Invalid input\n");
        return 1;
    }

    printf("Enter width: ");
    if (scanf("%lf", &width) != 1) {
        printf("Invalid input\n");
        return 1;
    }

    printf("Enter height: ");
    if (scanf("%lf", &height) != 1) {
        printf("Invalid input\n");
        return 1;
    }

    if (length <= 0 || width <= 0 || height <= 0) {
        printf("Dimensions must be positive\n");
        return 1;
    }

    volume = cuboid_volume(length, width, height);
    printf("Volume: %.2f\n", volume);

    return 0;
}