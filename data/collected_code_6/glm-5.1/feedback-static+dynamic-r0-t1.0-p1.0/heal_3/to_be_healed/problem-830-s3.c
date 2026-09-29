#include <stdio.h>
#include <math.h>
#include <errno.h>
#include <float.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 123.02, got <no output>
  *  test case 1 failed: expected 123.1, got <no output>
  *  test case 0 failed: expected 124, got <no output>
  */

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
    double res;
    
    errno = 0;
    res = round_up(123.954, 0);
    if (errno == 0) printf("%.0f\n", res);

    errno = 0;
    res = round_up(123.02, 1);
    if (errno == 0) printf("%.1f\n", res);

    errno = 0;
    res = round_up(123.015, 2);
    if (errno == 0) printf("%.2f\n", res);

    return 0;
}