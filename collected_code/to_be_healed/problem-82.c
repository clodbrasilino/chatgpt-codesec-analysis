#include <stdio.h>

float calculateVolume(float radius) {
    float volume;
    volume = (4.0/3.0) * 3.14159 * radius * radius * radius;
    return volume;
}

int main() {
    float radius, volume;
    printf("Enter the radius of the sphere: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'radius' is initialized [premium-bughuntingUninit]
     */
    scanf("%f", &radius);
    /* Possible weaknesses found:
     *  Cannot determine that 'radius' is initialized [premium-bughuntingUninit]
     */
    volume = calculateVolume(radius);
    printf("The volume of the sphere is %.2f\n", volume);
    return 0;
}