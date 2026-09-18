#include <stdio.h>
#include <math.h>

double find_third_side(double first_side, double second_side, int is_hypotenuse) {
    if(first_side < 0 || second_side < 0) {
        printf("Sides must be positive.\n");
        return -1;
    }
    if(is_hypotenuse == 1 && first_side > second_side) {
        return sqrt(pow(first_side,2) - pow(second_side,2));
    } else if(is_hypotenuse == 0) {
        return sqrt(pow(first_side,2) + pow(second_side,2));
    } else {
        printf("Check if the larger side is the hypotenuse.\n");
        return -1;
    }
}

int main() {
    double side1, side2;
    int is_hyp;

    printf("Enter first side of the triangle: ");
    scanf("%lf", &side1);
    printf("Enter second side of the triangle: ");
    scanf("%lf", &side2);
    printf("Is the first side the hypotenuse? (1 for yes, 0 for no): ");
    scanf("%d", &is_hyp);

    double third_side = find_third_side(side1, side2, is_hyp);

    if(third_side != -1) {
        printf("The third side of the triangle is: %.2lf\n", third_side);
    }

    return 0;
}