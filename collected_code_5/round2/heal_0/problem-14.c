#include <stdio.h>

double volume_of_prism(double base, double height_prism, double height_triangle) {
    if(base <= 0 || height_prism <= 0 || height_triangle <= 0) {
        printf("Dimensions of a prism cannot be less than or equal to zero.\n");
        return -1;
    }
   
    double volume = 0.5 * base * height_triangle * height_prism;

    return volume;
}

int main() {
    double base, height_prism, height_triangle;
    
    printf("Enter base of triangle: ");
    scanf("%lf", &base);

    printf("Enter height of triangle: ");
    scanf("%lf", &height_triangle);

    printf("Enter height of prism: ");
    scanf("%lf", &height_prism);

    double volume = volume_of_prism(base, height_prism, height_triangle);

    if(volume != -1) {
        printf("Volume of the prism: %lf\n", volume);
    }

    return 0;
}