#include <stdio.h>

float volume_of_cone(float radius, float height) {
    float volume = (1.0/3) * 3.14159 * radius * radius * height;
    return volume;
}

int main() {
    float radius, height;
    printf("Enter the radius and height of the cone: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'height' is initialized [premium-bughuntingUninit]
     *  Cannot determine that 'radius' is initialized [premium-bughuntingUninit]
     */
    scanf("%f %f", &radius, &height);

    /* Possible weaknesses found:
     *  Cannot determine that 'height' is initialized [premium-bughuntingUninit]
     *  Cannot determine that 'radius' is initialized [premium-bughuntingUninit]
     */
    float volume = volume_of_cone(radius, height);
    printf("The volume of the cone is: %.2f\n", volume);

    return 0;
}