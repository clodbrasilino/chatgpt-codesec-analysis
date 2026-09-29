#include <stdio.h>
#include <math.h>

double surfaceAreaOfCylinder(double radius, double height)
{
    if(radius <= 0 || height <= 0) return 0;
    double surfaceArea = 2 * M_PI * radius * (radius + height);

    return surfaceArea;
}

int main()
{
    double radius, height;
    printf("Enter the radius of the cylinder: ");
    scanf("%lf", &radius);

    printf("Enter the height of the cylinder: ");
    scanf("%lf", &height);

    double result = surfaceAreaOfCylinder(radius, height);
    
    if (result == 0) 
    {
        printf("Radius and height values should be greater that zero");
    } 
    else 
    {
        printf("Surface Area is: %f\n",result);
    }
    
    return 0;
}