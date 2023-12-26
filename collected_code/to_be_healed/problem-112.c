#include<stdio.h>

float findPerimeterOfCylinder(float radius, float height) {
    float perimeter;
    perimeter = 2 * 3.14 * radius + 2 * 3.14 * radius * height;
    return perimeter;
}

int main() {
    float radius, height;
    
    printf("Enter the radius of the cylinder: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'radius' is initialized [premium-bughuntingUninit]
     */
    scanf("%f", &radius);
    
    printf("Enter the height of the cylinder: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'height' is initialized [premium-bughuntingUninit]
     */
    scanf("%f", &height);
    
    /* Possible weaknesses found:
     *  Cannot determine that 'height' is initialized [premium-bughuntingUninit]
     *  Cannot determine that 'radius' is initialized [premium-bughuntingUninit]
     */
    float perimeter = findPerimeterOfCylinder(radius, height);
    
    printf("Perimeter of the cylinder is: %.2f\n", perimeter);
    
    return 0;
}