#include <stdio.h>
#include <math.h>

double find_third_side(double a, double b, int is_hypotenuse) {
    if (is_hypotenuse) {
        return sqrt(a * a + b * b);
    } else {
        if (a > b) {
            return sqrt(a * a - b * b);
        } else {
            return sqrt(b * b - a * a);
        }
    }
}

int main() {
    double side1, side2;
    int is_hypotenuse;

    printf("Enter side 1: ");
    scanf("%lf", &side1);
    printf("Enter side 2: ");
    scanf("%lf", &side2);
    printf("Is the longest side unknown? (1 for yes, 0 for no): ");
    scanf("%d", &is_hypotenuse);

    double third_side = find_third_side(side1, side2, is_hypotenuse);
    printf("The third side is: %.2lf\n", third_side);

    return 0;
}