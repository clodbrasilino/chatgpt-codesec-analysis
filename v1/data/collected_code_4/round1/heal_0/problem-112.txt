#include <stdio.h>
#include <math.h>

double cylinder_perimeter(double radius, double height) {
    if(radius <= 0 || height <= 0) {
        printf("Error: Radius and Height must be positive\n");
        return -1;
    }

    double perimeter = 2 * M_PI * radius * height;
    
    return perimeter;
}

int main() {
    double radius, height;

    printf("Enter the radius of the cylinder: ");
    scanf("%lf", &radius);
    
    printf("Enter the height of the cylinder: ");
    scanf("%lf", &height);
    
    double perimeter = cylinder_perimeter(radius, height);

    if(perimeter != -1)
        printf("The perimeter of the cylinder is: %.2f\n", perimeter);

    return 0;
}