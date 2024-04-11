#include <stdio.h>
#include <math.h>

int check_decimal_precision(double num) {
    double decimal_part = num - (int)num;
    decimal_part *= 100;
    int rounded_decimal_part = (int)(decimal_part + 0.5);
    if(rounded_decimal_part == (int)decimal_part) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    double num;
    printf("Enter a decimal number: ");
    scanf("%lf", &num);
    if(check_decimal_precision(num)) {
        printf("The number has a precision of 2 decimal places.\n");
    } else {
        printf("The number does not have a precision of 2 decimal places.\n");
    }
    return 0;
}