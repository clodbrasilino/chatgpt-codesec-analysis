#include <stdio.h>
#include <math.h>

double calculate_lateral_surface_area(double radius, double slant_height) {
    if (radius <= 0 || slant_height <= 0) {
        printf("Invalid inputs. Radius and slant_height must be greater than 0.\n");
        return -1;
    }
    
    double lateral_surface_area = M_PI * radius * slant_height;
    
    return lateral_surface_area;
}

int main() {
    double radius, slant_height;
    
    printf("Enter the radius of the cone: ");
    if(scanf("%lf", &radius) != 1) {
        printf("Entered input is not valid. Please enter a number.\n");
        return -1;
    }
    
    printf("Enter the slant_height of the cone: ");
    if(scanf("%lf", &slant_height) != 1) {
        printf("Entered input is not valid. Please enter a number.\n");
        return -1;
    }
    
    double result = calculate_lateral_surface_area(radius, slant_height);
    
    if(result != -1){
        printf("Lateral surface area of the cone is: %.2lf\n", result);
    }
    
    return 0;
}