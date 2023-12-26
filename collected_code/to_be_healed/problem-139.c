#include <stdio.h>

float findCircumference(float radius) {
    float circumference;
    
    circumference = 2 * 3.14159 * radius;
    
    return circumference;
}

int main() {
    float radius;
    
    printf("Enter the radius of the circle: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'radius' is initialized [premium-bughuntingUninit]
     */
    scanf("%f", &radius);
    
    /* Possible weaknesses found:
     *  Cannot determine that 'radius' is initialized [premium-bughuntingUninit]
     */
    float circumference = findCircumference(radius);
    
    printf("The circumference of the circle is: %f\n", circumference);
    
    return 0;
}