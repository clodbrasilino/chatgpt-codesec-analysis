#include <stdio.h>

float calculateVolume(float radius) {
    float volume;
    volume = (4.0 / 3.0) * 3.14159 * radius * radius * radius;
    return volume;
}

int main() {
    float radius = 0.0, volume = 0.0;
    printf("Enter the radius of the sphere: ");
    scanf("%f", &radius);
    volume = calculateVolume(radius);
    printf("The volume of the sphere is %.2f\n", volume);
    return 0;
}