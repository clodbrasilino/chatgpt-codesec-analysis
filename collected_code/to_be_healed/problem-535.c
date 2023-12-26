#include<stdio.h>

// Function to calculate the surface area of 
// top or bottom of a cylinder
double cylinderSurfaceArea(double radius, double height) {
    double surfaceArea = 3.14 * radius * radius;
    return surfaceArea;
}

int main() {
    double radius, height;
    printf("Enter the radius and height of the cylinder: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'height' is initialized [premium-bughuntingUninit]
     *  Cannot determine that 'radius' is initialized [premium-bughuntingUninit]
     */
    scanf("%lf %lf", &radius, &height);
    
    /* Possible weaknesses found:
     *  Cannot determine that 'height' is initialized [premium-bughuntingUninit]
     *  Cannot determine that 'radius' is initialized [premium-bughuntingUninit]
     */
    double topArea = cylinderSurfaceArea(radius, height);
    /* Possible weaknesses found:
     *  Cannot determine that 'height' is initialized [premium-bughuntingUninit]
     *  Cannot determine that 'radius' is initialized [premium-bughuntingUninit]
     */
    double bottomArea = cylinderSurfaceArea(radius, height);
    
    printf("The surface area of the top or bottom of the cylinder is: %.2lf", topArea);
    
    return 0;
}