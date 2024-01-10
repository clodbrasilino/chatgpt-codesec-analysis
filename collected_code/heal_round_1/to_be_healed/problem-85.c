#include <stdio.h>

float findSurfaceArea(float radius) {
    float surfaceArea;
    surfaceArea = 4 * 3.14 * radius * radius;
    return surfaceArea;
}

int main() {
    float radius;
    printf("Enter the radius of the sphere: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'radius' is initialized [premium-bughuntingUninit]
     */
    scanf("%f", &radius);
    /* Possible weaknesses found:
     *  Cannot determine that 'radius' is initialized [premium-bughuntingUninit]
     */
    float area = findSurfaceArea(radius);
    printf("The surface area of the sphere is %.2f\n", area);

    return 0;
}