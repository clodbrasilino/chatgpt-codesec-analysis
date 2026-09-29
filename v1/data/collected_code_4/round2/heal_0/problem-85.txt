#include <stdio.h>
#include <math.h>

#define PI 3.14159

double calculate_surface_area(double radius){
    return 4 * PI * pow(radius, 2);
}

int main(){
    double radius;

    printf("Enter the radius of the sphere: ");
    scanf("%lf", &radius);

    if(radius <= 0){
        printf("Radius should be a positive number.\n");
        return 1;
    }

    double area = calculate_surface_area(radius);

    printf("The surface area of the sphere is: %.2lf\n", area);

    return 0;
}