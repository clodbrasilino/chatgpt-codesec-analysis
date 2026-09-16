#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979323846

double find_minimum_periodic(double A, double B, double C, double D) {
    if (A < 0) {
        A = -A;
    }
    return D - A;
}

int main(void) {
    double A = 5.0;
    double B = 2.0;
    double C = 0.0;
    double D = 10.0;
    
    double min_value = find_minimum_periodic(A, B, C, D);
    
    printf("%.4f\n", min_value);
    
    return 0;
}