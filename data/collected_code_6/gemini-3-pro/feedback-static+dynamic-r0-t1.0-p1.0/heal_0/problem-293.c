#include <stdio.h>
#include <math.h>

double find_third_side(double side1, double side2, char side_to_find) {
    if (side1 <= 0.0 || side2 <= 0.0) {
        return -1.0;
    }

    if (side_to_find == 'h') {
        return sqrt((side1 * side1) + (side2 * side2));
    } else if (side_to_find == 'l') {
        if (side1 >= side2) {
            return sqrt((side1 * side1) - (side2 * side2));
        } else {
            return sqrt((side2 * side2) - (side1 * side1));
        }
    } else {
        return -1.0;
    }
}

int main(void) {
    double side1 = 0.0;
    double side2 = 0.0;
    char side_to_find = 0;
    double result = 0.0;

    if (scanf("%lf %lf %c", &side1, &side2, &side_to_find) != 3) {
        return 1;
    }

    result = find_third_side(side1, side2, side_to_find);

    if (result < 0.0) {
        return 1;
    }

    printf("%f\n", result);

    return 0;
}