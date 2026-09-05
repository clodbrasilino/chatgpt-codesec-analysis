#include <stdio.h>
#include <math.h>
#include <errno.h>

double find_third_side(double a, double b, int is_hypotenuse_known) {
    if (a <= 0 || b <= 0) {
        errno = EDOM;
        return -1.0;
    }

    if (is_hypotenuse_known) {
        if (b >= a) {
            errno = EDOM;
            return -1.0;
        }
        return sqrt(a * a - b * b);
    } else {
        return sqrt(a * a + b * b);
    }
}

int main() {
    double side1 = 3.0;
    double side2 = 4.0;
    double side3 = 5.0;
    double result;

    errno = 0;
    result = find_third_side(side1, side2, 0);
    if (errno != 0) {
        return 1;
    }
    printf("Hypotenuse: %f\n", result);

    errno = 0;
    result = find_third_side(side3, side1, 1);
    if (errno != 0) {
        return 1;
    }
    printf("Leg: %f\n", result);

    return 0;
}