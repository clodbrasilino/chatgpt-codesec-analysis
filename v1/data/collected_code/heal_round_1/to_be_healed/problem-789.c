#include <stdio.h>
#include <math.h>

double calculatePerimeter(double sides, double length) {
    return sides * length;
}

int main() {
    double sides, length, perimeter;
    
    printf("Enter the number of sides of the regular polygon: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'sides' is initialized [premium-bughuntingUninit]
     */
    scanf("%lf", &sides);
    
    printf("Enter the length of each side: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'length' is initialized [premium-bughuntingUninit]
     */
    scanf("%lf", &length);
    
    /* Possible weaknesses found:
     *  Cannot determine that 'length' is initialized [premium-bughuntingUninit]
     *  Cannot determine that 'sides' is initialized [premium-bughuntingUninit]
     */
    perimeter = calculatePerimeter(sides, length);
    
    printf("The perimeter of the regular polygon is: %.2f\n", perimeter);
    
    return 0;
}