#include <stdio.h>

float perimeter(float a, float b, float c) {
    return a + b + c;
}

int main() {
    float side1, side2, side3;
    printf("Enter the lengths of the three sides of the triangle: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'side2' is initialized [premium-bughuntingUninit]
     *  Cannot determine that 'side3' is initialized [premium-bughuntingUninit]
     *  Cannot determine that 'side1' is initialized [premium-bughuntingUninit]
     */
    scanf("%f %f %f", &side1, &side2, &side3);
    
    /* Possible weaknesses found:
     *  Cannot determine that 'side2' is initialized [premium-bughuntingUninit]
     *  Cannot determine that 'side3' is initialized [premium-bughuntingUninit]
     *  Cannot determine that 'side1' is initialized [premium-bughuntingUninit]
     */
    float result = perimeter(side1, side2, side3);
    printf("Perimeter of the triangle is: %.2f", result);
    
    return 0;
}