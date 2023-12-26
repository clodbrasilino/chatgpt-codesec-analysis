#include <stdio.h>

float findSurfaceArea(float length, float width, float height) {
    float surfaceArea = 2 * (length* width + length * height + width * height);
    return surfaceArea;
}

int main() {
    float length, width, height;
    printf("Enter the length, width, and height of the cuboid: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'height' is initialized [premium-bughuntingUninit]
     *  Cannot determine that 'width' is initialized [premium-bughuntingUninit]
     *  Cannot determine that 'length' is initialized [premium-bughuntingUninit]
     */
    scanf("%f %f %f", &length, &width, &height);
    
    /* Possible weaknesses found:
     *  Cannot determine that 'height' is initialized [premium-bughuntingUninit]
     *  Cannot determine that 'width' is initialized [premium-bughuntingUninit]
     *  Cannot determine that 'length' is initialized [premium-bughuntingUninit]
     */
    float area = findSurfaceArea(length, width, height);
    printf("The surface area of the cuboid is: %.2f", area);
    
    return 0;
}