#include<stdio.h>
#include<math.h>

double surfaceAreaSquarePyramid(double base, double slant_height) {
    if (base < 0 || slant_height < 0) {
        return -1;
    }
    return (base * base) + (2 * base * slant_height);
}

int main() {
    double base, slant_height;

    printf("Enter the base of the pyramid: ");
    scanf("%lf", &base);

    printf("Enter the slant height of the pyramid: ");
    scanf("%lf", &slant_height);

    double result = surfaceAreaSquarePyramid(base, slant_height);
    
    if(result != -1) {
        printf("The surface area of the square pyramid is: %.2lf units\n", result); 
    } else {
        printf("The base and the slant height of the pyramid should be a non-negative numbers\n");
    }
    
    return 0;
}