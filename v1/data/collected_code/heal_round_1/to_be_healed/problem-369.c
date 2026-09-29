#include <stdio.h>

float lateral_surface_area(float length, float breadth, float height) {
    float lsa = 2 * (length * height + breadth * height);
    return lsa;
}

int main() {
    float length, breadth, height;
    printf("Enter length, breadth, and height of the cuboid: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'height' is initialized [premium-bughuntingUninit]
     *  Cannot determine that 'length' is initialized [premium-bughuntingUninit]
     *  Cannot determine that 'breadth' is initialized [premium-bughuntingUninit]
     */
    scanf("%f %f %f", &length, &breadth, &height);
    /* Possible weaknesses found:
     *  Cannot determine that 'height' is initialized [premium-bughuntingUninit]
     *  Cannot determine that 'length' is initialized [premium-bughuntingUninit]
     *  Cannot determine that 'breadth' is initialized [premium-bughuntingUninit]
     */
    float area = lateral_surface_area(length, breadth, height);
    printf("Lateral surface area of the cuboid is: %.2f\n", area);
    return 0;
}