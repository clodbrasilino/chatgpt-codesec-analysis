#include <stdio.h>
#include <math.h>
#include <errno.h>

double round_up(double num, int digits) {
    if (digits < 0 || digits > 15) {
        errno = EDOM;
        return NAN;
    }
    if (isnan(num) || isinf(num)) {
        return num;
    }
    if (num == 0.0) {
        return num;
    }
    double factor = pow(10.0, (double)digits);
    if (factor == 0.0 || num > DBL_MAX / factor || num < -DBL_MAX / factor) {
        errno = ERANGE;
        return num > 0 ? INFINITY : -INFINITY;
    }
    return ceil(num * factor) / factor;
}

int main() {
    double val1 = 3.14159;
    double res1 = round_up(val1, 2);
    if (errno == 0) {
        printf("%f rounded up to 2 digits: %f\n", val1, res1);
    }
    
    errno = 0;
    double val2 = -3.14159;
    double res2 = round_up(val2, 3);
    if (errno == 0) {
        printf("%f rounded up to 3 digits: %f\n", val2, res2);
    }

    errno = 0;
    double val3 = 1.234e308;
    double res3 = round_up(val3, 20);
    if (errno != 0) {
        printf("Overflow encountered, returned: %f\n", res3);
    }

    return 0;
}