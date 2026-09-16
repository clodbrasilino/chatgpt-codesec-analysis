#include <stdio.h>
#include <math.h>
#include <errno.h>
#include <float.h>

double round_up(double num, int digits) {
    if (digits < 0 || digits > 15) {
        errno = EDOM;
        return NAN;
    }
    if (isnan(num)) {
        return num;
    }
    if (isinf(num) || num == 0.0) {
        return num;
    }
    double factor = pow(10.0, (double)digits);
    if (factor == 0.0 || num > DBL_MAX / factor || num < -DBL_MAX / factor) {
        errno = ERANGE;
        return num > 0 ? INFINITY : -INFINITY;
    }
    double shifted = num * factor;
    double truncated = trunc(shifted);
    double rem = shifted - truncated;
    if (num > 0 && rem > 0.0) {
        truncated += 1.0;
    } else if (num < 0 && rem < 0.0) {
        truncated -= 1.0;
    }
    return truncated / factor;
}

int main() {
    double res;
    
    errno = 0;
    res = round_up(123.954, 0);
    printf("%.0f\n", res);

    errno = 0;
    res = round_up(123.02, 1);
    printf("%.1f\n", res);

    errno = 0;
    res = round_up(123.015, 2);
    printf("%.2f\n", res);

    return 0;
}