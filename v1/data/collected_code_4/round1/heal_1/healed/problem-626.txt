#include <stdio.h>
#include <math.h>

#define PI 3.141592653589793

double calculate_triangle(double r) {

    if(r <= 0) {
        printf("Error: Radius cannot be less or equal to 0\n");
        return -1;
    }
    
    double h = r;
    double base = 2 * r; 
    
    double area = 0.5 * base * h;
    return area;
}

void inscribed_triangle() {
    double r;
    
    printf("Enter the radius of the semicircle: ");
    scanf("%lf", &r);
    
    double area = calculate_triangle(r);
    
    if(area > 0) {
        printf("The maximum area of an inscribed triangle in the semicircle with r = %.2lf is %.2lf\n", r, area);
    } 
}

int main() {
    inscribed_triangle();
    return 0;
}