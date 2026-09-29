#include <stdio.h>
#include <math.h>

double findThirdSide(double side1, double side2, char missingSideType) {
    if (side1 <= 0.0 || side2 <= 0.0) {
        return -1.0;
    }

    if (missingSideType == 'h' || missingSideType == 'H') {
        return sqrt((side1 * side1) + (side2 * side2));
    } else if (missingSideType == 'c' || missingSideType == 'C') {
        if (side1 >= side2) {
            return sqrt((side1 * side1) - (side2 * side2));
        } else {
            return sqrt((side2 * side2) - (side1 * side1));
        }
    }
    return -1.0;
}

int main(void) {
    double side1 = 0.0;
    double side2 = 0.0;
    double result = 0.0;
    char type = 0;

    printf("Enter two known sides: ");
    if (scanf("%lf %lf", &side1, &side2) != 2) {
        printf("Invalid input for sides.\n");
        return 1;
    }

    printf("What is missing? Enter 'h' for hypotenuse or 'c' for cathetus: ");
    if (scanf(" %c", &type) != 1) {
        printf("Invalid input for type.\n");
        return 1;
    }

    result = findThirdSide(side1, side2, type);

    if (result < 0.0) {
        printf("Error calculates the third side. Check your inputs.\n");
        return 1;
    }

    printf("The third side is: %.2lf\n", result);

    return 0;
}