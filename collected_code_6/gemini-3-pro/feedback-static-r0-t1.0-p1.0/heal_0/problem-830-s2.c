#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double round_up_to_digits(double num, int digits) {
    if (digits < 0) {
        return num;
    }
    double multiplier = pow(10.0, digits);
    return ceil(num * multiplier) / multiplier;
}

int main(void) {
    double number = 12.34567;
    int digits = 3;
    
    double rounded = round_up_to_digits(number, digits);
    
    printf("%.5f rounded up to %d decimal places is %.*f\n", number, digits, digits, rounded);
    
    return EXIT_SUCCESS;
}