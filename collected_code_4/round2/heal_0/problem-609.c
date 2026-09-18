#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979323846

double getMinimumValue(double a, double b, double c) {
    double min_val = a;
    for(double x = 0; x <= 2 * PI; x += 0.01) {
        double value = a * sin(b * x + c);
        if(value < min_val) {
            min_val = value;
        }
    }
    return min_val;
}

int main() {
    double a, b, c;
    printf("Enter a, b, and c for the periodic function: ");
    if(scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        printf("Invalid input!");
        return 1;
    }

    double min_value = getMinimumValue(a, b, c);
    printf("The minimum value of the function is: %f\n", min_value);
    return 0;
}