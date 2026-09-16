#include <stdio.h>
#include <math.h>

int checkRoots(double a, double b, double c) {
    if (a == 0) {
        return 0;
    }

    if (b == 0) {
        double discriminant = (b * b) - (4 * a * c);
        if (discriminant >= 0) {
            return 1;
        }
    }

    return 0;
}

int main(void) {
    double a = 1.0;
    double b = 0.0;
    double c = -4.0;

    int result = checkRoots(a, b, c);

    if (result) {
        printf("The roots are numerically equal but opposite in sign.\n");
    } else {
        printf("The roots are NOT numerically equal but opposite in sign.\n");
    }

    return 0;
}