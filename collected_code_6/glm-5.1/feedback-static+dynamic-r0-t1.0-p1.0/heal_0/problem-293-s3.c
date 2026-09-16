#include <stdio.h>
#include <math.h>
#include <errno.h>

double find_third_side(double side1, double side2, int is_hypotenuse_unknown) {
    if (side1 <= 0.0 || side2 <= 0.0) {
        errno = EDOM;
        return NAN;
    }
    if (is_hypotenuse_unknown) {
        return sqrt((side1 * side1) + (side2 * side2));
    } else {
        if (side1 >= side2) {
            errno = EDOM;
            return NAN;
        }
        return sqrt((side2 * side2) - (side1 * side1));
    }
}

int main() {
    double s1 = 3.0;
    double s2 = 4.0;
    double hyp = find_third_side(s1, s2, 1);
    if (errno == EDOM) {
        return 1;
    }
    printf("%f\n", hyp);
    
    errno = 0;
    double leg = find_third_side(s1, hyp, 0);
    if (errno == EDOM) {
        return 1;
    }
    printf("%f\n", leg);
    
    return 0;
}