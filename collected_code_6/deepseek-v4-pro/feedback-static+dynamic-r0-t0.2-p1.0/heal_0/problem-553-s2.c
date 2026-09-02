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
    int exp = t.exponent;
    
    while (exp > 0) {
        result *= 10.0;
        exp--;
    }
    while (exp < 0) {
        result /= 10.0;
        exp++;
    }
    
    if (t.sign < 0) {
        result = -result;
    }
    
    return result;
}

int main(void) {
    Tuple t1 = {1, 314159, -5};
    Tuple t2 = {-1, 271828, -5};
    Tuple t3 = {1, 0, 10};
    Tuple t4 = {1, 12345, 2};
    
    printf("%f\n", tuple_to_float(t1));
    printf("%f\n", tuple_to_float(t2));
    printf("%f\n", tuple_to_float(t3));
    printf("%f\n", tuple_to_float(t4));
    
    return 0;
}