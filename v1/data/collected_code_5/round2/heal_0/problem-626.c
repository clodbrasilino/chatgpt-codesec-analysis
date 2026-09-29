#include <stdio.h>
#include <math.h>

#define PI 3.14159265

double maxTriangleAreaInSemiCircle(double radius) {
    double area;
    if(radius <= 0) {
         printf("Radius should be a positive number!\n");
         return 0;
    }
    area = (1.0 / 2.0) * radius * radius * sin(PI); 
    return area;
}

int main() {
    double radius;
    printf("Enter the radius of the semicircle: ");
    scanf("%lf", &radius);
    if (radius <= 0) {
        printf("Input should be a positive number!\n");
        return 0;
    }

    double result = maxTriangleAreaInSemiCircle(radius);
    printf("The largest possible area of a triangle inscribed in the given semicircle is %lf \n", result);

    return 0;
}