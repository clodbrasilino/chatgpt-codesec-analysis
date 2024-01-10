#include <stdio.h>
#include <math.h>

double findThirdSide(double side1, double side2) {
    double thirdSide = sqrt((side1 * side1) + (side2 * side2));
    return thirdSide;
}

int main() {
    double side1, side2;
    
    printf("Enter the length of the first side: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'side1' is initialized [premium-bughuntingUninit]
     */
    scanf("%lf", &side1);
    
    printf("Enter the length of the second side: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'side2' is initialized [premium-bughuntingUninit]
     */
    scanf("%lf", &side2);
    
    /* Possible weaknesses found:
     *  Cannot determine that 'side2' is initialized [premium-bughuntingUninit]
     *  Cannot determine that 'side1' is initialized [premium-bughuntingUninit]
     */
    double thirdSide = findThirdSide(side1, side2);
    
    printf("The length of the third side is %.2lf\n", thirdSide);
    
    return 0;
}