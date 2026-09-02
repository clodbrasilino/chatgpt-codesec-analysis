#include <stdio.h>
#include <math.h>

int check_decimal_precision(double num) {
    double diff = num - round(num * 100) / 100;
    return fabs(diff) < 1e-9;
}

int main() {
    double number = 123.45;
    if (check_decimal_precision(number)) {
        printf("Number has a precision of 2.\n");
    } else {
        printf("Number does not have a precision of 2.\n");
    }
    return 0;
}