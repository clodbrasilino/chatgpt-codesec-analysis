#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double tuple_to_float(int integer_part, int fractional_part) {
    if (fractional_part < 0) {
        return 0.0; 
    }

    double fraction = (double)fractional_part;
    while (fraction >= 1.0) {
        fraction /= 10.0;
    }

    double result = (double)integer_part;
    if (integer_part < 0) {
        result -= fraction;
    } else {
        result += fraction;
    }

    return result;
}

int main(void) {
    int integer_part = 42;
    int fractional_part = 56;

    double result = tuple_to_float(integer_part, fractional_part);
    printf("%f\n", result);

    integer_part = -3;
    fractional_part = 1415;
    result = tuple_to_float(integer_part, fractional_part);
    printf("%f\n", result);

    return 0;
}