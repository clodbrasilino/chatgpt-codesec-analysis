#include <stdio.h>
#include <math.h>

typedef struct Complex {
    double real;
    double imag;
} Complex;

typedef struct Polar {
    double r;
    double theta;
} Polar;

Polar toPolar(Complex c);

int main() {
    Complex c;

    printf("Enter real part: ");
    scanf("%lf", &c.real);
    printf("Enter imaginary part: ");
    scanf("%lf", &c.imag);

    Polar p = toPolar(c);
    printf("The polar form is %.2lf(cos(%.2lf) + isin(%.2lf))\n", p.r, p.theta, p.theta);

    return 0;
}

Polar toPolar(Complex c) {
    Polar p;

    p.r = sqrt(c.real * c.real + c.imag * c.imag);
    p.theta = atan2(c.imag, c.real);

    return p;
}