#include<stdio.h>

float findPerimeterOfCylinder(float radius, float height) {
    float perimeter;
    perimeter = 2 * 3.14 * radius + 2 * 3.14 * radius * height;
    return perimeter;
}

int main() {
    float radius, height;
    
    printf("Enter the radius of the cylinder: ");
    scanf("%f", &radius);
    
    printf("Enter the height of the cylinder: ");
    scanf("%f", &height);
    
    float perimeter = findPerimeterOfCylinder(radius, height);
    
    printf("Perimeter of the cylinder is: %.2f\n", perimeter);
    
    return 0;
}