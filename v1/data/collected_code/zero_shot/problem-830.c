#include <math.h>

double roundUpToDigits(double number, int digits) {
    double multiplier = pow(10.0, digits);
    double roundedNumber = ceil(number * multiplier) / multiplier;
    return roundedNumber;
}