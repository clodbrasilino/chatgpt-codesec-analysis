#include <stdio.h>

float findCircumference(float radius) {
    float circumference;
    
    circumference = 2 * 3.14159 * radius;
    
    return circumference;
}

int main() {
    float radius = 0.0;

    printf("Enter the radius of the circle: ");
    scanf("%f", &radius);
    
    float circumference = findCircumference(radius);
    
    printf("The circumference of the circle is: %f\n", circumference);
    
    return 0;
}