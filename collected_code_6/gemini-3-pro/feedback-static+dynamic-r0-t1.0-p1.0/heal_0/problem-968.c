#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979323846

double find_max_periodic(double A, double B) {
    return sqrt(A * A + B * B);
}

int main() {
    double A = 3.0;
    double B = 4.0;
    
    double max_val = find_max_periodic(A, B);
    
    printf("The maximum value of %f*cos(t) + %f*sin(t) is %f\n", A, B, max_val);
    
    return 0;
}