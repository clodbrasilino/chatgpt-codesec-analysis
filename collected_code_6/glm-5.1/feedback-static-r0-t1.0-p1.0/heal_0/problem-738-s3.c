#include <stdio.h>
#include <math.h>
#include <errno.h>

double geometric_sum(double r, int n) {
    if (n < 1) {
        errno = EDOM;
        return NAN;
    }
    if (r == 1.0) {
        return (double)(n - 1);
    }
    return (1.0 - pow(r, (double)(n - 1))) / (1.0 - r);
}

int main() {
    double r = 2.0;
    int n = 5;
    
    errno = 0;
    double result = geometric_sum(r, n);
    
    if (errno != 0) {
        return 1;
    }
    
    printf("%f\n", result);
    
    return 0;
}