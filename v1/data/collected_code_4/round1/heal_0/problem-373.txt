#include <stdio.h>

double volume_of_cuboid(double length, double width, double height) {
    double volume;
    volume = length * width * height;
    return volume;
}

int main () {
    double length, width, height;

    printf("Enter length of the cuboid: ");
    scanf("%lf", &length);
    if(length <= 0)
    {
        printf("Length must be a positive number.\n");
        return 1;
    }

    printf("Enter width of the cuboid: ");
    scanf("%lf", &width);
    if(width <= 0)
    {
        printf("Width must be a positive number.\n");
        return 1;
    }

    printf("Enter height of the cuboid: ");
    scanf("%lf", &height);
    if(height <= 0)
    {
        printf("Height must be a positive number.\n");
        return 1;
    }

    double volume = volume_of_cuboid(length, width, height);
    printf("The volume of the cuboid is: %.2lf\n", volume);
     
    return 0;
}
