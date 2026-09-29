#include<stdio.h>

double lateral_surface_area(double length, double width, double height) {
    return 2 * (length * height + width * height);
}

int main() {
    double length, width, height;

    printf("Enter the length, width and height of the cuboid respectively:\n");
    if(scanf("%lf %lf %lf", &length, &width, &height) != 3) {
        printf("Invalid input. Program terminated.\n");
        return 1;
    }
   
    if(length <= 0 || width <= 0 || height <= 0) {
        printf("Invalid dimensions provided. Dimensions must be greater than 0. Program terminated.\n");
        return 1;
    }

    printf("The lateral surface area of the cuboid is: %.2lf\n", lateral_surface_area(length, width, height));

    return 0;
}