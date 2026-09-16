#include <stdio.h>
#include <math.h>

typedef struct {
    double real;
    double imag;
} ComplexNumber;

double get_complex_length(ComplexNumber c);

double get_complex_length(ComplexNumber c) {
    return hypot(c.real, c.imag);
}

int main(void) {
    ComplexNumber c = {3.0, 4.0};
    
    double length = get_complex_length(c);
    
    if (printf("%.6f\n", length) < 0) {
        return 1;
    }
    
    return 0;
}