#include <stdio.h>
#include <math.h>

int check_decimal_precision(double num) {
    double integral, fractional;
    fractional = modf(num, &integral);
    fractional *= 100;
    fractional = round(fractional);
    return (fractional == (int)fractional);
}

int main() {
    double num = 12.34;
    if(check_decimal_precision(num)) {
        printf("The number has a precision of 2 decimal places.\n");
    } else {
        printf("The number does not have a precision of 2 decimal places.\n");
    }
    return 0;
}