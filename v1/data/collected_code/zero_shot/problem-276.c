#include<stdio.h>

float findVolumeOfCylinder(float radius, float height) {
    float volume;
    volume = 3.14159 * radius * radius * height;
    return volume;
}

int main() {
    float radius, height, volume;
    printf("Enter the radius of the cylinder: ");
    scanf("%f", &radius);
    printf("Enter the height of the cylinder: ");
    scanf("%f", &height);
    volume = findVolumeOfCylinder(radius, height);
    printf("The volume of the cylinder is: %.2f", volume);
    return 0;
}