#include <stdio.h>

float volume_of_cone(float radius, float height) {
    float volume = (1.0/3) * 3.14159 * radius * radius * height;
    return volume;
}

int main() {
    float radius = 0.0, height = 0.0;

    printf("Enter the radius and height of the cone: ");
    scanf("%f %f", &radius, &height);

    float volume = volume_of_cone(radius, height);
    printf("The volume of the cone is: %.2f\n", volume);

    return 0;
}