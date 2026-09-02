#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int sign;
    unsigned long long mantissa;
    int exponent;
} Tuple;

double tuple_to_float(Tuple t) {
    if (t.mantissa == 0) {
        return 0.0;
    }
    
    double result = (double)t.mantissa;
    result = ldexp(result, t.exponent);
    
    if (t.sign < 0) {
        result = -result;
    }
    
    return result;
}

int main(void) {
    Tuple t1 = {1, 12345, -3};
    Tuple t2 = {-1, 98765, 2};
    Tuple t3 = {1, 0, 10};
    
    printf("%f\n", tuple_to_float(t1));
    printf("%f\n", tuple_to_float(t2));
    printf("%f\n", tuple_to_float(t3));
    
    return 0;
}