#include<stdio.h>

double findSurfaceArea(double radius, double height) {
    double baseArea = 3.14159 * radius * radius;
    double lateralArea = 2 * 3.14159 * radius * height;
    double surfaceArea = 2 * baseArea + lateralArea;
    return surfaceArea;
}

int main() {
    double radius, height;
    printf("Enter the radius of the cylinder: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'radius' is initialized [premium-bughuntingUninit]
     */
    scanf("%lf", &radius);
    printf("Enter the height of the cylinder: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'height' is initialized [premium-bughuntingUninit]
     */
    scanf("%lf", &height);

    /* Possible weaknesses found:
     *  Cannot determine that 'height' is initialized [premium-bughuntingUninit]
     *  Cannot determine that 'radius' is initialized [premium-bughuntingUninit]
     */
    double area = findSurfaceArea(radius, height);
    printf("Surface area of the cylinder: %.2lf\n", area);

    return 0;
}