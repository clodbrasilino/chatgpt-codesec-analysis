#include <stdio.h>

#define PI 3.14159

float calculateArcLength(float radius, float angle) {
    float arcLength;

    arcLength = (angle / 360) * (2 * PI * radius);

    return arcLength;
}

int main() {
    float radius, angle, result;

    printf("Enter the radius of the circle: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'radius' is initialized [premium-bughuntingUninit]
     */
    scanf("%f", &radius);

    printf("Enter the angle in degrees: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'angle' is initialized [premium-bughuntingUninit]
     */
    scanf("%f", &angle);

    /* Possible weaknesses found:
     *  Cannot determine that 'angle' is initialized [premium-bughuntingUninit]
     *  Cannot determine that 'radius' is initialized [premium-bughuntingUninit]
     */
    result = calculateArcLength(radius, angle);

    printf("The arc length is: %f\n", result);

    return 0;
}