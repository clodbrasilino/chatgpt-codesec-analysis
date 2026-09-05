#include <stdio.h>
#include <math.h>
#include <float.h>
#include <errno.h>

double cylinder_volume(double radius, double height) {
    errno = 0;
    if (radius < 0.0 || height < 0.0) {
        errno = EDOM;
        return 0.0;
    }
    if (radius > sqrt(DBL_MAX / M_PI) || height > DBL_MAX) {
        errno = ERANGE;
        return HUGE_VAL;
    }
    return M_PI * radius * radius * height;
}

int main(void) {
    double radius = 5.0;
    double height = 10.0;
    double volume = cylinder_volume(radius, height);
    
    if (errno == EDOM) {
        return 1;
    }
    if (errno == ERANGE) {
        return 2;
    }
    
    printf("%f\n", volume);
    return 0;
}