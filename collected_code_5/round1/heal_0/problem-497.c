#include <stdio.h>
#include <math.h>

#define PI 3.141592653589793

double coneSurfaceArea(double r, double h) {
    if(r <= 0 || h <= 0)
        return -1;
    
    double l = sqrt(r * r + h * h);
  
    return PI * r * (r + l);
}

int main() {
    double r, h;
    
    printf("Enter radius of the cone: ");
    scanf("%lf", &r);
    
    printf("Enter height of the cone: ");
    scanf("%lf", &h);
    
    double surfaceArea = coneSurfaceArea(r, h);
    
    if(surfaceArea == -1) {
        printf("Invalid input.\n");
    } else {
        printf("Surface area of the cone is: %.2lf\n", surfaceArea);
    }

    return 0;
}