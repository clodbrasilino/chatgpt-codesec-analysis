#include <stdio.h>
#include <math.h>

double findThirdSide(double side1, double side2) {
    double thirdSide = sqrt((side1 * side1) + (side2 * side2));
    return thirdSide;
}

int main() {
    double side1 = 0.0, side2 = 0.0;
    
    printf("Enter the length of the first side: ");
    scanf("%lf", &side1);
    
    printf("Enter the length of the second side: ");
    scanf("%lf", &side2);
    
    double thirdSide = findThirdSide(side1, side2);
    
    printf("The length of the third side is %.2lf\n", thirdSide);
    
    return 0;
}