#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double tuple_to_float(int integer_part, int fractional_part) {
    if (fractional_part < 0) {
        return -1.0; 
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
    /* Possible weaknesses found:
     *  Assignment 'int_part=42', assigned value is 42
     */
    int int_part = 42;
    int frac_part = 567;

    double result = tuple_to_float(int_part, frac_part);
    
    /* Possible weaknesses found:
     *  Condition 'int_part==-1' is always false
     *  Condition 'int_part==-1' is always false [knownConditionTrueFalse]
     */
    if (result != -1.0 || (int_part == -1 && frac_part == 0)) {
        printf("%f\n", result);
    } else {
        printf("Invalid input\n");
    }

    return 0;
}