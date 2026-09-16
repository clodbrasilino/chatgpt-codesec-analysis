#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double round_up_to_digits(double value, int digits) {
    if (digits < 0) {
        return value; 
    }
    
    double multiplier = pow(10.0, digits);
    return ceil(value * multiplier) / multiplier;
}

int main(void) {
    double num1 = 12.341;
    double num2 = 45.678;
    double num3 = -9.876;
    
    int digits1 = 2;
    int digits2 = 1;
    int digits3 = 0;
    
    double res1 = round_up_to_digits(num1, digits1);
    double res2 = round_up_to_digits(num2, digits2);
    double res3 = round_up_to_digits(num3, digits3);
    
    printf("%.3f rounded up to %d digits: %.*f\n", num1, digits1, digits1, res1);
    printf("%.3f rounded up to %d digits: %.*f\n", num2, digits2, digits2, res2);
    printf("%.3f rounded up to %d digits: %.*f\n", num3, digits3, digits3, res3);
    
    return 0;
}