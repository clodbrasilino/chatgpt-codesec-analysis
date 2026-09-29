#include <stdio.h>

float findFocus(float a, float b, float c) {
    return (b * b - 4 * a * c) / (4 * a);
}

int main() {
    float a, b, c;
    printf("Enter the coefficients of the quadratic equation (ax^2 + bx + c): ");
    /* Possible weaknesses found:
     *  Cannot determine that 'c' is initialized [premium-bughuntingUninit]
     *  Cannot determine that 'b' is initialized [premium-bughuntingUninit]
     *  Cannot determine that 'a' is initialized [premium-bughuntingUninit]
     */
    scanf("%f %f %f", &a, &b, &c);
    
    /* Possible weaknesses found:
     *  Cannot determine that 'c' is initialized [premium-bughuntingUninit]
     *  Cannot determine that 'b' is initialized [premium-bughuntingUninit]
     *  Cannot determine that 'a' is initialized [premium-bughuntingUninit]
     */
    float focus = findFocus(a, b, c);

    printf("The focus of the parabola is: %f", focus);

    return 0;
}