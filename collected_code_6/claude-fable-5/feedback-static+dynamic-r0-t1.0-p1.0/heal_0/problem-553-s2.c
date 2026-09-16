#include <stdio.h>
#include <math.h>

double tuple_to_float(int whole, int fractional)
{
    int digits = 1;
    int temp = fractional;
    double divisor;

    if (fractional < 0) {
        fractional = -fractional;
        temp = fractional;
    }

    while (temp >= 10) {
        temp /= 10;
        digits++;
    }

    divisor = pow(10.0, (double)digits);

    if (whole < 0) {
        return (double)whole - ((double)fractional / divisor);
    }

    return (double)whole + ((double)fractional / divisor);
}

int main(void)
{
    int first = 4;
    int second = 56;
    double result;

    result = tuple_to_float(first, second);

    if (printf("Tuple (%d, %d) as float: %f\n", first, second, result) < 0) {
        return 1;
    }

    first = 7;
    second = 256;
    result = tuple_to_float(first, second);

    if (printf("Tuple (%d, %d) as float: %f\n", first, second, result) < 0) {
        return 1;
    }

    first = -3;
    second = 14;
    result = tuple_to_float(first, second);

    if (printf("Tuple (%d, %d) as float: %f\n", first, second, result) < 0) {
        return 1;
    }

    return 0;
}